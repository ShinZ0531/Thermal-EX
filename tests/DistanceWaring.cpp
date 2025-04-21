#include "Config.h"
#include "Ultrasonic/HCSR04.h"
#include "LED/LEDController.h"
#include "Keyboard/KeyboardInputMonitor.h"
#include "SG90/SG90Controller.h"
#include <iostream>
#include <atomic>

class UltrasonicRangingCallback : public HCSR04::HCSR04CallbackInterface {
    public:
        UltrasonicRangingCallback(LEDController& ledRef, SG90Controller& sg90Ref, int threshold)
            : led(ledRef), sg90(sg90Ref), distanceThreshold(threshold),
              lastState(false), debounceCounter(0) {}
    
        virtual void hasHCSR04Sample(EchoPulse sample) override {
            float distance = sample.durationMicros() * SOUND_SPEED / 2.0f;
            printf("Distance: %.2f cm\n", distance);
    
            bool nearTarget = (distance < distanceThreshold);
    
            if (nearTarget != lastState) {
                debounceCounter++;
                if (debounceCounter >= 3) {
                    updateState(nearTarget);
                    lastState = nearTarget;
                    debounceCounter = 0;
                }
            } else {
                debounceCounter = 0;
            }
        }
    
    private:
        void updateState(bool isTracking) {
            led.setBlinkInterval(isTracking ? 100 : 1000);
    
            if (isTracking) {
                sg90.stopScanning();
                sg90.setMode(SG90Mode::TRACKING);
            } else {
                sg90.setMode(SG90Mode::SCANNING);
                sg90.startScanning();
            }
        }
    
        LEDController& led;
        SG90Controller& sg90;
        int distanceThreshold;
        bool lastState;
        int debounceCounter;
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
                    keyboard_.setIsWorkningTrue();
                    std::cout << "System STARTED" << std::endl;
                }
                break;
            
            case 'q':
            case 'Q':
                if (running_) {
                    sensor_.stopRanging();
                    led_.stopLED();
                    running_ = false;
                    keyboard_.setIsWorkningFalse();
                    std::cout << "System STOPPED" << std::endl;
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
    KeyboardInputMonitor keyboard_;
    bool running_ = false;
};

int main() {
    try {
        HCSR04 sensor;
        LEDController led;
        KeyboardInputMonitor keyboard;
        SG90Controller sg90(0, 0);
        sg90.setSpeed(20);
        sg90.enableSG90();
        sg90.setAngleSmooth(90);
        UltrasonicRangingCallback ultrasonic_cb(led, sg90, 30);
        KeyboardHandler keyboard_cb(led, sensor);

        sensor.registerCallback(&ultrasonic_cb);
        keyboard.registerCallback(&keyboard_cb);

        std::cout << "Press S to start, Q to quit" << std::endl;
        keyboard.startKeyboardInput();

        while (keyboard.getIsWorking()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        sg90.disableSG90();
        keyboard.stopKeyboardInput();   
        // sensor.stopRanging();
        // led.stopLED();
        

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}