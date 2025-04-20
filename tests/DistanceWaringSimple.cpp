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
    
    



int main() {
    HCSR04 sensor;
    try {
        
        LEDController led;
        SG90Controller sg90(0, 0);
        UltrasonicRangingCallback ultrasonic_cb(led, sg90, 30);
        sensor.registerCallback(&ultrasonic_cb);

        sg90.enableSG90();
        sg90.setSpeed(20);
        sg90.setAngleSmooth(90);
        sg90.setMode(SG90Mode::SCANNING);

        getchar();   
        led.startLED();
        sensor.startRanging();

        std::cout << "Press enter to quit.\n" << std::endl;

        getchar();
        sensor.stopRanging();
        led.stopLED();
        sg90.disableSG90();
        
        // std::this_thread::sleep_for(std::chrono::seconds(10));
        printf("Turn off\n");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}