#include "LED/LEDController.h"
#include "Arknights/Arknights.h"
#include <iostream>

/**
 * @brief Entry point for the application.
 * 
 * @return Integer 0 upon exit success, non-zero on error.
 */

class LEDChangeCallback : public LEDController::LEDCallbackInterface {
public:
    LEDChangeCallback(LEDController& ledRef) : led(ledRef) {}
    virtual void hasLEDSample(int sample) override {
        printf("LED blink interval changed to %d ms\n", sample);
        led.setBlinkInterval(sample); 
	}
private:
    LEDController& led;
};


int main() {
    Arknights::printLogo();
    
    try {
        LEDController led;
        LEDChangeCallback ledChangeCallback(led);
        led.registerCallback(&ledChangeCallback);

        led.startLED();
        int isBlinking = 1;
        while (isBlinking) isBlinking = led.waitForKeyboardInput();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}