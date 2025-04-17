#include "Config.h"
#include "Ultrasonic/HCSR04.h"
#include <iostream>


class HCSR04Printer : public HCSR04::HCSR04CallbackInterface {
    virtual void hasHCSR04Sample(EchoPulse sample) override {
        float distance = sample.durationMicros() * SOUND_SPEED / 2.0f;
		printf("Distance: %.2f cm\n", distance);
	}
};

int main() {
    try {
        HCSR04 sensor;
        HCSR04Printer printer;
        sensor.registerCallback(&printer);
        // DataLogger logger("ultrasonic_measurements.csv");
        printf("Press Enter to start ranging, press again to stop ranging.\n");
        getchar();
        sensor.startRanging();
        getchar();
	    sensor.stopRanging();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}