#pragma once

/*
===========================================================
        L200 NEXUS ACP
        L200 Nexus ACP Automotive Control Platform V2.3
===========================================================

Author : Matty
Platform : ESP32 NodeMCU-32S
Framework : PlatformIO

*/

#include <Arduino.h>

//
//----------------------------------------------------------
// Firmware
//----------------------------------------------------------
//

#define FW_NAME            "L200 NEXUS ACP"
#define FW_VERSION         "2.3.0"
#define HW_REVISION        "Rev A"

#define DEVICE_NAME        "L200-NEXUS"

//
//----------------------------------------------------------
// BLE UUIDs
//----------------------------------------------------------
//

#define SERVICE_UUID       "D7F0A100-3E91-4C25-9D8A-001122334455"

#define COMMAND_UUID       "D7F0A101-3E91-4C25-9D8A-001122334455"

#define STATUS_UUID        "D7F0A102-3E91-4C25-9D8A-001122334455"

#define CONFIG_UUID        "D7F0A103-3E91-4C25-9D8A-001122334455"

#define RGB_UUID           "D7F0A104-3E91-4C25-9D8A-001122334455"

#define OTA_UUID           "D7F0A105-3E91-4C25-9D8A-001122334455"

//
//----------------------------------------------------------
// GPIO Outputs
//----------------------------------------------------------
//

#define PIN_LOCK_RELAY         16

#define PIN_UNLOCK_RELAY       17

#define PIN_IGNITION_RELAY     18

#define PIN_STARTER_RELAY      19

#define PIN_HEADLIGHT_RELAY    21

#define PIN_RGB                22

//
//----------------------------------------------------------
// Inputs
//----------------------------------------------------------
//

#define PIN_ENGINE_RUNNING     34

#define PIN_BATTERY_SENSE      35

#define PIN_DOOR_TRIGGER       32

#define PIN_IGNITION_INPUT     33

//
//----------------------------------------------------------
// RGB
//----------------------------------------------------------
//

#define RGB_LED_COUNT          12

#define RGB_DEFAULT_BRIGHTNESS         120

//
//----------------------------------------------------------
// Relay Timing
//----------------------------------------------------------
//

#define LOCK_PULSE_TIME        250

#define UNLOCK_PULSE_TIME      250

#define STARTER_TIME           800

#define ENGINE_RETRY_DELAY     2500

//
//----------------------------------------------------------
// WiFi
//----------------------------------------------------------
//

#define WIFI_AP_NAME           "L200-NEXUS"

#define WIFI_AP_PASSWORD       "L200Nexus"

//
//----------------------------------------------------------
// HTTP
//----------------------------------------------------------
//

#define HTTP_PORT              80

//
//----------------------------------------------------------
// OTA
//----------------------------------------------------------
//

#define OTA_HOSTNAME           "L200-NEXUS"

//
//----------------------------------------------------------
// RGB Scenes
//----------------------------------------------------------
//

enum class RGBScene
{
    OFF,

    BOOT,

    IDLE,

    BLE_ADVERTISING,

    BLE_CONNECTED,

    LOCKING,

    UNLOCKING,

    IGNITION,

    STARTING,

    ENGINE_RUNNING,

    LOW_BATTERY,

    OVERHEAT,

    ALARM,

    OTA,

    FAULT
};

//
//----------------------------------------------------------
// Vehicle Commands
//----------------------------------------------------------
//

enum class VehicleCommand
{
    NONE,

    LOCK,

    UNLOCK,

    IGNITION_ON,

    IGNITION_OFF,

    START_ENGINE,

    STOP_ENGINE,

    HEADLIGHT_ON,

    HEADLIGHT_OFF,

    STATUS,

    RGB
};

//
//----------------------------------------------------------
// System Constants
//----------------------------------------------------------
//

constexpr uint32_t STATUS_UPDATE_MS = 500;

constexpr uint32_t BLE_NOTIFY_MS    = 250;

constexpr uint32_t RGB_UPDATE_MS    = 20;

constexpr uint32_t WIFI_UPDATE_MS   = 1000;

constexpr uint32_t HEARTBEAT_MS     = 1000;
