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
#include <functional>

/**
 * @brief Manages the main operations about light on and off of the application.
 * 
 * LED will be on and off with the interval.
 * 
 * Target light should link to GPIO line LED_BCM_PIN.
 */
class LEDController {
public:
    LEDController();
    ~LEDController();

    struct LEDCallbackInterface {
	    /**
	     * Called when a new sample is available.
	     * This needs to be implemented in a derived
	     * class by the client. Defined as abstract.
	     * \param sample rising edge time and falling edge time
	     **/
	virtual void hasLEDSample(int sample) = 0;
    };

	void registerCallback(LEDCallbackInterface* ci) {
		ledCallbackInterfaces.push_back(ci);
	}

    void startLED();
    void LEDBlinking();
    void stopLED();
    void turnOn();
    void turnOff();
    void setBlinkInterval(int interval);
    void notifyCallbacks(int interval);
    int getLEDBlinkInterval();
    void waitForStart();
    int waitForKeyboardInput();
private:
    std::vector<LEDCallbackInterface*> ledCallbackInterfaces;
    struct gpiod_line* ledLine;
    bool isActive_;
    std::thread workerThread_;
    std::thread keybordThread_;
    int blinkIntervalMs;
    const char* chipName = "gpiochip0";
    
    void initializeGPIO();
};

#endif