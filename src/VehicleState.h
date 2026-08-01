#pragma once

#include <Arduino.h>

class VehicleState
{
public:
    // Door Locks
    bool locked = true;

    // Power / Ignition
    bool ignition = false;
    bool engineRunning = false;
    bool accessories = false;

    // Lighting
    bool headlights = false;

    // Telemetry
    float batteryVoltage = 0.0f;
    float coolantTemp = 0.0f;
    float oilPressure = 0.0f;
    int rpm = 0;

    // Connectivity
    bool connectedBLE = false;
    bool connectedWiFi = false;
};

extern VehicleState Vehicle;
