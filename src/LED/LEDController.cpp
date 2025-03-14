#include "LEDController.h"
#include "Config.h"

LEDController::LEDController() : isActive(false), blinkIntervalMs(BLINK_INTERVAL_MS) {
    initializeGPIO();
}

void LEDController::initializeGPIO() {
    // open GPIO chip
    struct gpiod_chip* chip = gpiod_chip_open_by_name(chipName);
    if (!chip) {
        throw std::runtime_error("Failed to open GPIO chip");
    }

    // get GPIO line LED_BCM_PIN
    ledLine = gpiod_chip_get_line(chip, LED_BCM_PIN);
    if (!ledLine) {
        gpiod_chip_close(chip);
        throw std::runtime_error("Failed to get GPIO line 23");
    }

    // set output mode
    if (gpiod_line_request_output(ledLine, "LEDControl", 0) < 0) {
        gpiod_chip_close(chip);
        throw std::runtime_error("Failed to set output mode");
    }
}

LEDController::~LEDController() {
    if (ledLine) {
        gpiod_line_release(ledLine);
        gpiod_chip_close(gpiod_line_get_chip(ledLine));
    }
}

void LEDController::startBlinking() {
    isActive = true;
    while (isActive) {
        // High level, light on
        gpiod_line_set_value(ledLine, 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(blinkIntervalMs));
        // Low level, light off
        gpiod_line_set_value(ledLine, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(blinkIntervalMs));
    }
}

void LEDController::stopBlinking() {
    isActive = false;
}   

/**
 * @brief Set the time gap between on and off
 * 
 * @param interval  time gap
 */
void LEDController::setBlinkInterval(int interval) {
    if (interval > 0) blinkIntervalMs = interval;
}