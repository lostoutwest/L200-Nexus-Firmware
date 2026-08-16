#pragma once

#include <Arduino.h>

enum class SensorMode : uint8_t
{
    LOCKED = 0,
    UNLOCKED = 1,
    DRIVING = 2
};

class SensorManager
{
public:
    void begin();
    void update();

    bool available() const;
    SensorMode mode() const;

private:
    bool readRegister(uint8_t reg, uint8_t& value);
    bool writeRegister(uint8_t reg, uint8_t value);
    bool readAcceleration(float& x, float& y, float& z);
    void selectMode();

    bool sensorAvailable = false;
    uint8_t sensorAddress = 0x1C;
    SensorMode currentMode = SensorMode::LOCKED;
    float previousMagnitude = 1.0f;
    float previousPitch = 0.0f;
    float previousRoll = 0.0f;
    unsigned long lastUpdate = 0;
};

extern SensorManager Sensors;
