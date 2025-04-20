#include "Config.h"
#include "Ultrasonic/HCSR04.h"
#include "LED/LEDController.h"
#include "Keyboard/KeyboardInputMonitor.h"
#include <iostream>
#include <atomic>

// 原子操作标志位用于线程安全退出
std::atomic<bool> exit_flag(false);

class UltrasonicRangingCallback : public HCSR04::HCSR04CallbackInterface {
public:
    UltrasonicRangingCallback(LEDController& ledRef, int threshold) 
        : led(ledRef), 
          distanceThreshold(threshold),
          lastState(false), 
          debounceCounter(0) {} 

    virtual void hasHCSR04Sample(EchoPulse sample) override {
        float distance = sample.durationMicros() * SOUND_SPEED / 2.0f;
        printf("Distance: %.2f cm\n", distance);
    
        bool currentState = (distance < distanceThreshold);

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

    try {
        UltrasonicRangingCallback ultrasonic_cb(led, 30);
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

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        sensor.stopRanging();
        led.stopLED();
        keyboard.stopKeyboardInput();
    }
    return 0;
}