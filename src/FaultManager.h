#pragma once

#include <Arduino.h>

class FaultManager {
public:
    void begin();
    void update();
};

extern FaultManager Faults;
