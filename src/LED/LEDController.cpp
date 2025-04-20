#include "LEDController.h"
#include "Config.h"

LEDController::LEDController() : isActive_(false), blinkIntervalMs(BLINK_INTERVAL) {
    initializeGPIO();
}

LEDController::~LEDController() {
    stopLED();
}

void LEDController::initializeGPIO() {
    // open GPIO chip
    struct gpiod_chip* chip = gpiod_chip_open_by_name(chipName);
    if (!chip) {
        throw std::runtime_error("[LED] Failed to open GPIO chip");
    }

    // get GPIO line LED_BCM_PIN
    ledLine = gpiod_chip_get_line(chip, LED_BCM_PIN);
    if (!ledLine) {
        gpiod_chip_close(chip);
        throw std::runtime_error("[LED] Failed to get GPIO line " + std::to_string(LED_BCM_PIN));
    }

    // set output mode
    if (gpiod_line_request_output(ledLine, "LEDControl", 0) < 0) {
        gpiod_chip_close(chip);
        throw std::runtime_error("[LED] Failed to set output mode");
    }
}

void LEDController::startLED() {
    isActive_ = true;
    workerThread_ = std::thread(&LEDController::LEDBlinking, this);
    // keybordThread_ = std::thread(&LEDController::waitForKeyboardInput, this);
}

void LEDController::LEDBlinking() {
    isActive_ = true;
    while (isActive_) {
        // High level, light on
        gpiod_line_set_value(ledLine, 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(blinkIntervalMs));
        // Low level, light off
        gpiod_line_set_value(ledLine, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(blinkIntervalMs));
    }
}

void LEDController::stopLED() {
    if (!isActive_) return;
    isActive_ = false;

    if (workerThread_.joinable()) workerThread_.join();
    if (keybordThread_.joinable()) keybordThread_.join();

    if (ledLine) {
        gpiod_line_release(ledLine);
        auto* chip = gpiod_line_get_chip(ledLine);
        gpiod_chip_close(chip);
        ledLine = nullptr;
    }
} 

/**
 * @brief Set the time gap between on and off
 * 
 * @param interval  time gap
 */
void LEDController::setBlinkInterval(int interval) {
    if (interval > 0) 
    {
        blinkIntervalMs = interval;
        // changeBlinkInterval(interval);
    }
    else throw std::runtime_error("[LED] Failed to set blink interval. It must be positive number");
}
    
void LEDController::turnOn() {
    gpiod_line_set_value(ledLine, 1);
}

void LEDController::turnOff() {
    gpiod_line_set_value(ledLine, 0);
}

int LEDController::getLEDBlinkInterval() {
    return blinkIntervalMs;
}


void LEDController::notifyCallbacks(int interval) {
    for(auto &cb: ledCallbackInterfaces) {
        cb->hasLEDSample(interval);
    }
}

void LEDController::waitForStart() {
    printf("Press s to start ranging, press q to stop ranging.\n");
        while(isActive_){
            char keyboardInput = getchar();
            if (keyboardInput == 's') 
            {
                LEDController::startLED();
                int nowBlinkInterval = LEDController::getLEDBlinkInterval();
                printf("Now LED blink interval is %d ms\n", nowBlinkInterval);
                break;
            }
            else if (keyboardInput == 'q') 
            {
                LEDController::stopLED();
                break;
            }
        }
}

int LEDController::waitForKeyboardInput() {
    printf("Press 1-9 to change the LED blink interval to 100-900ms, and 0 means 1000ms.\n");
    while(isActive_){
        char input = getchar();
        if (input == 'q') {
            stopLED();
            return 0;
            break;
        }
        else if (input >= '0' && input <= '9'){
            int interval;
            if (input == '0') interval = 1000;
            else interval = (input - '0') * 100;
            
            notifyCallbacks(interval);
        }
    }
    return 0;
}