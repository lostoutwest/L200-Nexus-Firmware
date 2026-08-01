#pragma once

#include <Arduino.h>

class BLEManager {
public:
    void begin();
    void update();
};

extern BLEManager BLE;
