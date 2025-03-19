#include "Ultrasonic/ultrasonic.h"
#include "Ultrasonic/ultrasonicCalculator.h"
#include "Ultrasonic/DataLogger.h"
#include <iostream>

int main() {
    try {
        hcsr04 sensor;
        DataLogger logger("ultrasonic_measurements.csv");

        sensor.startRanging([&logger](const EchoPulse& pulse) {
        float distance = DistanceCalculator::calculate(pulse);

        MeasurementResult data{pulse, distance};

        logger.log(data);

        std::cout << "Distance: " << distance << " cm\n";
        });

        // main
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}