#pragma once

#include <Arduino.h>

namespace Pins
{
    // Relay Outputs
    constexpr uint8_t LockRelay       = 16;
    constexpr uint8_t UnlockRelay     = 17;
    constexpr uint8_t IgnitionRelay   = 18;
    constexpr uint8_t StarterRelay    = 19;
    constexpr uint8_t HeadlightRelay  = 21;
    constexpr uint8_t AccessoryRelay = 22;
    constexpr uint8_t HornRelay      = 23;

    // RGB
    constexpr uint8_t RGB             = 5;

    // Inputs
    constexpr uint8_t BatterySense    = 34;
    constexpr uint8_t CoolantSense     = 35;
    constexpr uint8_t OilSense        = 32;
    constexpr uint8_t RPMSense        = 33;
    constexpr uint8_t AmbientSense    = 39;
    constexpr uint8_t MotionSense     = 36;
}

constexpr uint32_t SERIAL_BAUD = 115200;
