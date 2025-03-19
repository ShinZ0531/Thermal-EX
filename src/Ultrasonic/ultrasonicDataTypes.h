#pragma once
#include <chrono>

/**
 * @brief It is used to record the time when the signal rises and falls.
 * 
 */
struct EchoPulse {
    std::chrono::high_resolution_clock::time_point risingEdge;
    std::chrono::high_resolution_clock::time_point fallingEdge;
    int64_t durationMicros() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(
            fallingEdge - risingEdge
        ).count();
    }
};

/**
 * @brief It is used to record the result of ultrasonic measurement.
 * 
 */
struct MeasurementResult {
    EchoPulse pulse;
    float distanceCM;
};