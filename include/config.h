#ifndef CONFIG_H
#define CONFIG_H

#define SERIAL_BAUD 115200

namespace Pins
{
    // Relay Pins
    constexpr uint8_t LockRelay = 16;
    constexpr uint8_t UnlockRelay = 17;
    constexpr uint8_t IgnitionRelay = 18;
    constexpr uint8_t StarterRelay = 19;
    constexpr uint8_t HeadlightRelay = 20;
    constexpr uint8_t AccessoryRelay = 21;
    constexpr uint8_t HornRelay = 22;

    // RGB Hardware
    constexpr uint8_t PIN_RGB_DATA = 5;
    constexpr uint8_t NUM_LEDS = 14;
}
#define RGB_BRIGHTNESS_DEFAULT 75 // ~30% of 255

//==================================================
// L200 NEXUS ACP v2 BLE UUIDs
//==================================================

#define DEVICE_NAME        "L200-NEXUS"

#define SERVICE_UUID       "D7F0A100-3E91-4C25-9D8A-001122334455"

#define COMMAND_UUID       "D7F0A101-3E91-4C25-9D8A-001122334455"

#define STATUS_UUID        "D7F0A102-3E91-4C25-9D8A-001122334455"

#define CONFIG_UUID        "D7F0A103-3E91-4C25-9D8A-001122334455"

#define RGB_UUID           "D7F0A104-3E91-4C25-9D8A-001122334455"

#define OTA_UUID           "D7F0A105-3E91-4C25-9D8A-001122334455"

namespace Timing
{
    constexpr uint16_t LockPulseMs     = 300;
    constexpr uint16_t StarterMaxMs    = 1200;
    constexpr uint16_t RGBFrameMs      = 20;
    constexpr uint16_t AutoLockMs      = 30000;
}

#endif // CONFIG_H