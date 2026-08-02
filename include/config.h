#ifndef CONFIG_H
#define CONFIG_H

#define SERIAL_BAUD 115200

// Relay Pins
#define PIN_RELAY_LOCK_A 16
#define PIN_RELAY_LOCK_B 17
#define PIN_RELAY_IGNITION 18
#define PIN_RELAY_STARTER 19
#define PIN_RELAY_HEADLIGHTS 20
#define PIN_RELAY_ACCESSORIES 21
#define PIN_RELAY_HORN 22

// RGB Hardware
#define PIN_RGB_DATA 5
#define NUM_LEDS 14
#define RGB_BRIGHTNESS_DEFAULT 75 // ~30% of 255

// BLE UUIDs
#define SERVICE_UUID      "12345678-1234-1234-1234-123456789001"
#define COMMAND_UUID      "12345678-1234-1234-1234-123456789002"
#define STATUS_UUID       "12345678-1234-1234-1234-123456789003"

namespace Timing
{
    constexpr uint16_t LockPulseMs     = 300;
    constexpr uint16_t StarterMaxMs    = 1200;
    constexpr uint16_t RGBFrameMs      = 20;
    constexpr uint16_t AutoLockMs      = 30000;
}

#endif // CONFIG_H