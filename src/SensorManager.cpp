#include "../include/SensorManager.h"

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include "../include/Config.h"
#include "../include/Logger.h"
#include "../include/RGBManager.h"
#include "../include/VehicleController.h"

namespace
{
    constexpr uint8_t MMA8452Q_WHO_AM_I = 0x0D;
    constexpr uint8_t MMA8452Q_OUT_X_MSB = 0x01;
    constexpr uint8_t MMA8452Q_XYZ_DATA_CFG = 0x0E;
    constexpr uint8_t MMA8452Q_CTRL_REG1 = 0x2A;
    constexpr uint8_t MMA8452Q_EXPECTED_ID = 0x2A;
}

SensorManager Sensors;

void SensorManager::begin()
{
    Wire.begin(PIN_SENSOR_SDA, PIN_SENSOR_SCL);
    Wire.setClock(400000);

    uint8_t id = 0;
    for (uint8_t address : {uint8_t(0x1C), uint8_t(0x1D)})
    {
        sensorAddress = address;
        if (readRegister(MMA8452Q_WHO_AM_I, id) && id == MMA8452Q_EXPECTED_ID)
        {
            sensorAvailable = true;
            break;
        }
    }

    if (!sensorAvailable)
    {
        Log.warning("[SENSOR] MMA8452Q not detected at 0x1C or 0x1D");
        return;
    }

    // Standby while configuring, ±2 g range, then active at 200 Hz.
    writeRegister(MMA8452Q_CTRL_REG1, 0x00);
    writeRegister(MMA8452Q_XYZ_DATA_CFG, 0x00);
    writeRegister(MMA8452Q_CTRL_REG1, 0x11);

    lastUpdate = millis();
    Log.info(String("[SENSOR] MMA8452Q ready at 0x") + String(sensorAddress, HEX));
}

void SensorManager::update()
{
    if (!sensorAvailable || !readAcceleration(
        Vehicle.state().accelX,
        Vehicle.state().accelY,
        Vehicle.state().accelZ))
        return;

    selectMode();

    const float x = Vehicle.state().accelX;
    const float y = Vehicle.state().accelY;
    const float z = Vehicle.state().accelZ;
    const float magnitude = sqrtf(x * x + y * y + z * z);

    Vehicle.state().pitch = atan2f(x, sqrtf(y * y + z * z)) * 57.2957795f;
    Vehicle.state().roll = atan2f(y, sqrtf(x * x + z * z)) * 57.2957795f;

    const float accelerationDelta = fabsf(magnitude - previousMagnitude);
    const float pitchDelta = fabsf(Vehicle.state().pitch - previousPitch);
    const float rollDelta = fabsf(Vehicle.state().roll - previousRoll);

    Vehicle.state().motionDetected =
        accelerationDelta >= SENSOR_MOTION_DELTA_G ||
        fabsf(x) >= SENSOR_MOTION_AXIS_G ||
        fabsf(y) >= SENSOR_MOTION_AXIS_G ||
        fabsf(z - 1.0f) >= SENSOR_MOTION_AXIS_G;

    Vehicle.state().tiltDetected =
        pitchDelta >= SENSOR_TILT_DELTA_DEG ||
        rollDelta >= SENSOR_TILT_DELTA_DEG ||
        fabsf(Vehicle.state().pitch) >= SENSOR_TILT_ANGLE_DEG ||
        fabsf(Vehicle.state().roll) >= SENSOR_TILT_ANGLE_DEG;

    if (currentMode == SensorMode::LOCKED)
    {
        if (Vehicle.state().motionDetected || Vehicle.state().tiltDetected)
        {
            Vehicle.state().tamperDetected = true;
            Lighting.setScene(RGBScene::ALARM);
        }
    }
    else if (currentMode == SensorMode::UNLOCKED)
    {
        Vehicle.state().tamperDetected = false;
    }
    else
    {
        Vehicle.state().tamperDetected = false;
    }

    previousMagnitude = magnitude;
    previousPitch = Vehicle.state().pitch;
    previousRoll = Vehicle.state().roll;
    lastUpdate = millis();
}

void SensorManager::selectMode()
{
    if (Vehicle.state().engineRunning || Vehicle.state().ignition)
        currentMode = SensorMode::DRIVING;
    else if (Vehicle.state().locked)
        currentMode = SensorMode::LOCKED;
    else
        currentMode = SensorMode::UNLOCKED;

    Vehicle.state().sensorMode = static_cast<uint8_t>(currentMode);
}

bool SensorManager::available() const
{
    return sensorAvailable;
}

SensorMode SensorManager::mode() const
{
    return currentMode;
}

bool SensorManager::readRegister(uint8_t reg, uint8_t& value)
{
    Wire.beginTransmission(sensorAddress);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0 || Wire.requestFrom(sensorAddress, uint8_t(1)) != 1)
        return false;

    value = Wire.read();
    return true;
}

bool SensorManager::writeRegister(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(sensorAddress);
    Wire.write(reg);
    Wire.write(value);
    return Wire.endTransmission() == 0;
}

bool SensorManager::readAcceleration(float& x, float& y, float& z)
{
    Wire.beginTransmission(sensorAddress);
    Wire.write(MMA8452Q_OUT_X_MSB);
    if (Wire.endTransmission(false) != 0 || Wire.requestFrom(sensorAddress, uint8_t(6)) != 6)
        return false;

    auto readAxis = []() -> int16_t
    {
        int16_t raw = static_cast<int16_t>((Wire.read() << 8) | Wire.read());
        return raw >> 4;
    };

    x = readAxis() * 0.0009765625f;
    y = readAxis() * 0.0009765625f;
    z = readAxis() * 0.0009765625f;
    return true;
}
