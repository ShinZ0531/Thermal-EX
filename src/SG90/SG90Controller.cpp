#include "SG90Controller.h"
#include "Config.h"
#include <chrono>
#include <thread>

SG90Controller::SG90Controller(int pwm_channel, int pwm_chip) 
    : currentAngle(SG90_DEFAULT_ANGLE), targetAngle(90.0f), 
      moveSpeed(SG90_DEFAULT_SPEED), isActive_(false), smoothMode(true) {
    // Check if the PWM channel and chip are valid
    if(pwm_channel < 0 || pwm_channel > 1) {
        throw std::invalid_argument("Invalid PWM channel. Must be 0 or 1.");
    }
    if(pwm_chip < 0 || pwm_chip > 2) {
        throw std::invalid_argument("Invalid PWM chip. Must be 0 or 1.");
    }
    // Initialize GPIO for SG90 servo motor
    if(pwm.start(pwm_channel, PWM_FREQ, 0.0f, pwm_chip) < 0) {
        throw std::runtime_error("Failed to initialize PWM");
    }
    currentMode.store(SG90Mode::SCANNING);
}

SG90Controller::~SG90Controller() {
    stopScanning();
    disableSG90();
}

float SG90Controller::angleToDuty(float angle) const {
    angle = fmaxf(0.0f, fminf(180.0f, angle));
    const float pulseWidth = MIN_PULSE + (MAX_PULSE - MIN_PULSE) * (angle / 180.0f);
    return (pulseWidth * 1e-6) * PWM_FREQ * 100.0f;
}

void SG90Controller::updatePWM() {
    using namespace std::chrono;
    
    auto lastTime = steady_clock::now();
    
    while(isActive_) {
        auto now = steady_clock::now();
        float dt = duration_cast<duration<float>>(now - lastTime).count();
        lastTime = now;

        std::lock_guard<std::mutex> lock(dataMutex);
        float angle = currentAngle;
        float target = targetAngle;

        if (smoothMode) {
            float diff = target - angle;
            if (fabsf(diff) > 0.5f) {
                float step = moveSpeed * dt;
                angle += (diff > 0 ? 1 : -1) * fminf(fabsf(diff), step);
                currentAngle = angle;
            } else {
                currentAngle = target;
            }
        } else {
            angle = target;
        }

        pwm.setDutyCycle(angleToDuty(angle));
        std::this_thread::sleep_for(SG90_UPDATE_INTERVAL);
    }
}


void SG90Controller::setAngle(float angle) {
    std::lock_guard<std::mutex> lock(dataMutex);
    smoothMode = false;
    targetAngle = fmaxf(0.0f, fminf(180.0f, angle));
}

void SG90Controller::setAngleSmooth(float angle) {
    std::lock_guard<std::mutex> lock(dataMutex);
    smoothMode = true;
    targetAngle = fmaxf(0.0f, fminf(180.0f, angle));
}

void SG90Controller::setSpeed(float deg_per_sec) {
    moveSpeed = fmaxf(1.0f, fminf(180.0f, deg_per_sec));
}

void SG90Controller::enableSG90() {
    if(!isActive_.load()) {
        isActive_ .store(true);
        pwmThread = std::thread(&SG90Controller::updatePWM, this);
    }
}

void SG90Controller::disableSG90() {
    if(!isActive_) return;
    isActive_ = false;
    
    if(pwmThread.joinable()) pwmThread.join();
 
    pwm.stop();
}

int SG90Controller::waitForKeyboardInput() {
    printf("Input positive number between 0 to 180, to change the angle of servo motor SG90, press 999 to quit.\n");
    float inputAngle;
    while(isActive_){
        std::cin >> inputAngle;
        if (inputAngle == 999) {
            disableSG90();
            return 0;
            break;
        }
        else if (inputAngle < 0 || inputAngle > 180){
            printf("Invalid input. Please enter a number between 0 and 180.\n");
        } 
        else {
            notifyCallbacks(inputAngle);
        }
    }
    return 0;
}

int SG90Controller::waitForKeyboardInputFixed() {
    printf("Input a number, to change the angle of servo motor SG90, press 999 to quit.\n");
    printf("Positive means add 10 degrees, negative means minus 10 degrees.\n");
    float inputAngle;
    while(isActive_){
        std::cin >> inputAngle;
        if (inputAngle == 999) {
            
            return 0;
            break;
        }
        else {
            notifyCallbacks(inputAngle);
        }
    }
    return 0;
}

void SG90Controller::notifyCallbacks(float angle) {
    for(auto &cb: sg90CallbackInterfaces) {
        cb->hasSG90Sample(angle);
    }
}

void SG90Controller::change15Angle(float delta) {

    std::lock_guard<std::mutex> lock(angleLock);
    float newAngle;
    if (delta > 0) {
        newAngle = currentAngle + 15.0f;
    } else if (delta < 0) {
        newAngle = currentAngle - 15.0f;
    }

    newAngle = fmaxf(0.0f, fminf(180.0f, newAngle));
    currentAngle = newAngle;

    std::cout << "Target angle: " << newAngle << std::endl;
    setSpeed(20);
    setAngleSmooth(newAngle);
}

void SG90Controller::startScanning() {
    std::lock_guard<std::mutex> lock(modeMutex);
    stopScanThread = false;
    currentMode = SG90Mode::SCANNING;
    if (scanThread.joinable()) scanThread.join();
    scanThread = std::thread(&SG90Controller::scanningRoutine, this);
}

void SG90Controller::stopScanning() {
    std::lock_guard<std::mutex> lock(modeMutex);
    stopScanThread.store(true);
    if (scanThread.joinable()) scanThread.join();
}

void SG90Controller::scanningRoutine() {
    float angle = 60.0f;
    bool increasing = true;
    setSpeed(20);
    enableSG90();

    while (!stopScanThread) {
        setAngleSmooth(angle);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        if (increasing) {
            angle += 15.0f;
            if (angle >= 120.0f) increasing = false;
        } else {
            angle -= 15.0f;
            if (angle <= 60.0f) increasing = true;
        }
    }
}

void SG90Controller::trackTarget(float relativeOffset) {
    std::lock_guard<std::mutex> lock(dataMutex);
    if (currentMode != SG90Mode::TRACKING) return;

    float angle = currentAngle + relativeOffset * 15.0f; // -1~1 范围
    angle = std::max(0.0f, std::min(180.0f, angle));
    setSpeed(20);
    setAngleSmooth(angle);
}

void SG90Controller::setMode(SG90Mode mode) {
    std::lock_guard<std::mutex> lock(modeMutex);
    currentMode = mode;
}