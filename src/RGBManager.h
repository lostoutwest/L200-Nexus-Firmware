#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include "../include/config.h"

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

class RGBManager
{
public:
    void begin();
    void update();
    void setScene(RGBScene scene);
    void setBrightness(uint8_t brightness);

private:
    void handleAnimation();
    void updateHeartbeat();

    // Animation primitives
    void sweep(CRGB color, bool leftToRight, float speed);
    void breathe(CRGB color, float speed);
    void pulse(CRGB color, float speed);
    void chase(CRGB color, float speed);

    RGBScene currentScene = RGBScene::OFF;
    uint8_t currentBrightness = RGB_BRIGHTNESS_DEFAULT;

    unsigned long lastUpdate = 0;
    float animationPhase = 0.0f;
    unsigned long heartbeatTimer = 0;
};

extern RGBManager Lighting;
