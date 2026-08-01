#pragma once

#include <Arduino.h>

class OTAManager {
public:
    void begin();
    void update();
};

extern OTAManager OTA;
