#pragma once

#include <Arduino.h>

class SensorManager {
public:
    void begin();
    void update();
};

extern SensorManager Sensors;
