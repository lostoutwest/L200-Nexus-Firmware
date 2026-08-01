#pragma once

#include <Arduino.h>

class VehicleManager
{
public:
    void begin();
    void update();

    // High-level Control API
    void lock();
    void unlock();
    void startEngine();
    void stopEngine();
    void headlights(bool state);
    void accessories(bool state);
};

extern VehicleManager VehicleMgr;
