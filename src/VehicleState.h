#pragma once

#include <Arduino.h>

struct Diagnostics
{
    uint32_t bootCount = 0;
    uint32_t uptimeMs = 0;
    uint8_t faultCount = 0;
};

class VehicleState
{
public:

    //==================================================
    // Connection Status
    //==================================================

    bool bleConnected = false;

    bool wifiConnected = false;

    //==================================================
    // Vehicle Status
    //==================================================

    bool locked = true;

    bool ignition = false;

    bool engineRunning = false;

    bool headlights = false;

    bool accessories = false;

    bool horn = false;

    //==================================================
    // Live Sensor Values
    //==================================================

    float batteryVoltage = 0.0f;

    float coolantTemperature = 0.0f;

    float oilPressure = 0.0f;

    uint16_t rpm = 0;

    float ambientLight = 0.0f;

    bool motionDetected = false;

    //==================================================
    // System Diagnostics
    //==================================================

    Diagnostics diagnostics;

    //==================================================
    // Functions
    //==================================================

    void reset();
};

extern VehicleState Vehicle;
