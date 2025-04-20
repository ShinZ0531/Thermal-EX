#include "SG90/SG90Controller.h"
#include "Config.h"
#include <iostream>
#include <thread>
#include <chrono>

class SG90AngleFixedCallback : public SG90Controller::SG90CallbackInterface {
    public:
        SG90AngleFixedCallback(SG90Controller& servoRef) : servo(servoRef) {}
        virtual void hasSG90Sample(float angle) override {
            std::lock_guard<std::mutex> lock(callbackMutex);
            if (angle) printf("Angle plus 10 degree\n");
            else printf("Angle minus 10 degree\n");
            servo.change15Angle(angle);
        }
    
    private:
        SG90Controller& servo;
        std::mutex callbackMutex;
    };

class SG90AngleCallback : public SG90Controller::SG90CallbackInterface {
    public:
        SG90AngleCallback(SG90Controller& servoRef) : servo(servoRef) {}
        virtual void hasSG90Sample(float angle) override {
            std::lock_guard<std::mutex> lock(callbackMutex);
            printf("SG90 angle changed to %.2f\n", angle);
            servo.setAngleSmooth(angle);
        }
    
    private:
        SG90Controller& servo;
        std::mutex callbackMutex;
    };

int main() {
    try {
        SG90Controller servo(SG90_PWM_CHANNEL, SG90_PWM_CHIP);
        servo.enableSG90();

        // SG90AngleFixedCallback angleCallback(servo);
        SG90AngleCallback angleCallback(servo);
        servo.registerCallback(&angleCallback);

        std::cout << "[SG90] Go back to 90" << std::endl;
        servo.setSpeed(20);
        servo.setAngleSmooth(90);
        std::cout << "Waitting..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));

        int isWorking = 1;
        // while (isWorking) isWorking = servo.waitForKeyboardInputFixed();
        while (isWorking) isWorking = servo.waitForKeyboardInput();

        std::cout << "[SG90] Go back to 90" << std::endl;
        servo.setSpeed(20);
        servo.setAngleSmooth(90);
        std::cout << "Waitting..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));

        std::cout << "Turn off PWM" << std::endl;
        // servo.disableSG90();
    } catch (const std::exception& e) {
        std::cerr << "[SG90]Fail:" << e.what() << std::endl;
    }

    return 0;
}
