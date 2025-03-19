#pragma once
#include "ultrasonicDataTypes.h"
#include <fstream>
#include <mutex>

class DataLogger {
public:
    DataLogger(const std::string& filename);
    void log(const MeasurementResult& data);
    
private:
    std::ofstream logFile_;
    std::mutex fileMutex_;
};