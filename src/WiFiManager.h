#pragma once

#include <Arduino.h>

class WiFiManager {
public:
    void begin();
    void update();
};

extern WiFiManager WiFi;
