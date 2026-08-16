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
    bool bleConnected = false;
    bool wifiConnected = false;

    bool locked = true;
    bool ignition = false;
    bool engineRunning = false;
    bool headlights = false;
    bool accessories = false;
    bool horn = false;

    float batteryVoltage = 0.0f;
    float coolantTemperature = 0.0f;
    float oilPressure = 0.0f;
    uint16_t rpm = 0;
    float ambientLight = 0.0f;
    bool motionDetected = false;

    // MMA8452Q telemetry and anti-tamper state.
    float accelX = 0.0f;
    float accelY = 0.0f;
    float accelZ = 0.0f;
    float pitch = 0.0f;
    float roll = 0.0f;
    bool tiltDetected = false;
    bool tamperDetected = false;
    uint8_t sensorMode = 0; // 0=LOCKED, 1=UNLOCKED, 2=DRIVING

    Diagnostics diagnostics;

    void reset();
};
