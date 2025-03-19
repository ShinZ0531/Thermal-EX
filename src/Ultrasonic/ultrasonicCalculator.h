#pragma once

#include "ultrasonicDataTypes.h"
#include "Config.h"

class DistanceCalculator {
public:
    static float calculate(const EchoPulse& pulse) {
        return pulse.durationMicros() * SOUND_SPEED / 2.0f;
    }
};