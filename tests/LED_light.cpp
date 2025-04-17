#include "LED/LEDController.h"
#include "Arknights/Arknights.h"
#include <iostream>

/**
 * @brief Entry point for the application.
 * 
 * @return Integer 0 upon exit success, non-zero on error.
 */
int main() {
    Arknights::printLogo();
    
    try {
        LEDController led;
        printf("Press Enter to start ranging, press again to stop ranging.\n");
        getchar();
        led.startLED();
        getchar();
        led.stopLED();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}