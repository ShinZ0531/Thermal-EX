/**
 * @file LEDController.h
 * @brief Defines the LED class and associated functionality.
 */

#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H 

#include <gpiod.h>
#include <stdexcept>
#include <thread>
#include <chrono>

/**
 * @brief Manages the main operations about light on and off of the application.
 * 
 * LED will be on and off with the interval.
 * 
 * Target light should link to GPIO line LED_BCM_PIN.
 */
class LEDController {
private:
    struct gpiod_line* ledLine;
    bool isActive;
    int blinkIntervalMs;
    const char* chipName = "gpiochip0";

    
    void initializeGPIO();

public:
    explicit LEDController();
    ~LEDController();

    
    void startBlinking();
    void stopBlinking();
    void setBlinkInterval(int interval);
};

#endif