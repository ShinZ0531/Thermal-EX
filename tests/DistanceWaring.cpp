#include "Config.h"
#include "Ultrasonic/HCSR04.h"
#include "LED/LEDController.h"
#include "Keyboard/KeyboardInputMonitor.h"
#include "SG90/SG90Controller.h"
#include <iostream>
#include <atomic>

std::atomic<bool> exit_flag(false);

class UltrasonicRangingCallback : public HCSR04::HCSR04CallbackInterface {
    public:
        UltrasonicRangingCallback(LEDController& ledRef, SG90Controller& sg90Ref, int threshold) 
            : led(ledRef), sg90(sg90Ref),
              distanceThreshold(threshold),
              lastState(false), debounceCounter(0),
              shakeDirection(1), lastShakeTime(std::chrono::steady_clock::now()) {}
    
        virtual void hasHCSR04Sample(EchoPulse sample) override {
            float distance = sample.durationMicros() * SOUND_SPEED / 2.0f;
            printf("Distance: %.2f cm\n", distance);
    
            bool currentState = (distance < distanceThreshold);
    
            if (distance > 100.0f) {
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastShakeTime).count() > 1500) {
                    sg90.change15Angle(shakeDirection);
                    shakeDirection *= -1;
                    lastShakeTime = now;
                }
            } else {

            }
    
            if (currentState != lastState) {
                debounceCounter++;
                if (debounceCounter >= 3) {
                    updateLEDState(currentState);
                    lastState = currentState;
                    debounceCounter = 0;
                }
            } else {
                debounceCounter = 0;
            }
        }
    
    private:
        void updateLEDState(bool isDanger) {
            led.setBlinkInterval(isDanger ? 100 : 1000);
        }
    
        LEDController& led;
        SG90Controller& sg90;
        int distanceThreshold;
        bool lastState;
        int debounceCounter;
        int shakeDirection;
        std::chrono::steady_clock::time_point lastShakeTime;
    };
    

class KeyboardHandler : public KeyboardInputMonitor::KeyboardCallbackInterface {
public:
    KeyboardHandler(LEDController& led, HCSR04& sensor)
        : led_(led), sensor_(sensor) {}

    virtual void hasKeyboardSample(char key) override {
        switch(key) {
            case 's':
            case 'S':
                if (!running_) {
                    sensor_.startRanging();
                    led_.startLED();
                    running_ = true;
                    std::cout << "System STARTED safely." << std::endl;
                }
                break;
            
            case 'q':
            case 'Q':
                if (running_) {
                    sensor_.stopRanging();
                    led_.stopLED();
                    running_ = false;
                    exit_flag.store(true);
                    std::cout << "System STOPPED safely." << std::endl;
                }
                break;
            default:
                if (key >= 32 && key <= 126) {  // 可打印字符
                    std::cout << "Received: " << key << std::endl;
                }
        }
    }

private:
    LEDController& led_;
    HCSR04& sensor_;
    bool running_ = false;
};

int main() {
    HCSR04 sensor;
    LEDController led;
    KeyboardInputMonitor keyboard;
    SG90Controller sg90(0, 0);
    sg90.setSpeed(20);
    sg90.enableSG90();
    sg90.setAngleSmooth(90);

    try {
        UltrasonicRangingCallback ultrasonic_cb(led, sg90, 30);
        KeyboardHandler keyboard_cb(led, sensor);

        sensor.registerCallback(&ultrasonic_cb);
        keyboard.registerCallback(&keyboard_cb);

        std::cout << "Press S to start, Q to quit" << std::endl;
        keyboard.startKeyboardInput();

        while (!exit_flag.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        keyboard.stopKeyboardInput();   
        sensor.stopRanging();
        led.stopLED();
        sg90.disableSG90();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        sensor.stopRanging();
        led.stopLED();
        keyboard.stopKeyboardInput();
        sg90.disableSG90();
    }

    return 0;
}