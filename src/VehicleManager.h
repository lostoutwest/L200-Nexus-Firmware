#pragma once

#include <Arduino.h>

class VehicleManager
{
public:
    void begin();
    void update();

    // Public API for external requests (BLE/WiFi)
    void requestUnlock();
    void requestLock();
    void requestIgnition(bool state);
    void requestHeadlights(bool state);
};

extern VehicleManager VehicleMgr;
