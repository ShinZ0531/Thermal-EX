#include "DataLogger.h"

DataLogger::DataLogger(const std::string& filename) : logFile_(filename, std::ios::app) {
    if (!logFile_.is_open()) {
        throw std::runtime_error("[DataLogger] Can't open the file");
    }
    logFile_ << "Time stamp(us), distance (cm)\n";
}

void DataLogger::log(const MeasurementResult& data) {
    std::lock_guard<std::mutex> lock(fileMutex_);
    logFile_ << data.pulse.durationMicros() << "," << data.distanceCM << "\n";
}