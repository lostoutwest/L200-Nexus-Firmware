#include "../include/RGBManager.h"

CRGB leds[RGB_LED_COUNT];

RGBManager Lighting;

void RGBManager::begin()
{
    FastLED.addLeds<WS2812B, PIN_RGB, GRB>(leds, RGB_LED_COUNT);
    FastLED.setBrightness(currentBrightness);
    FastLED.clear();
    FastLED.show();

    setScene(RGBScene::OFF);
}

void RGBManager::setScene(RGBScene scene)
{
    if (currentScene == scene) return;

    currentScene = scene;
    animationPhase = 0.0f; // Reset animation when scene changes
}

void RGBManager::setBrightness(uint8_t brightness)
{
    currentBrightness = brightness;
    FastLED.setBrightness(currentBrightness);
}

void RGBManager::update()
{
    handleAnimation();
    updateHeartbeat();
    FastLED.show();
}

void RGBManager::handleAnimation()
{
    unsigned long now = millis();
    float delta = (now - lastUpdate) / 1000.0f;
    lastUpdate = now;
    animationPhase += delta;

    switch (currentScene)
    {
        case RGBScene::OFF:
            FastLED.clear();
            break;

        case RGBScene::BOOT:
            sweep(CRGB::White, true, 1.5f);
            break;

        case RGBScene::IDLE:
            // Dim warm white
            fill_solid(leds, RGB_LED_COUNT, CRGB(255, 200, 100));
            FastLED.setBrightness(currentBrightness / 4);
            break;

        case RGBScene::BLE_ADVERTISING:
            breathe(CRGB::Blue, 0.5f);
            break;

        case RGBScene::BLE_CONNECTED:
            fill_solid(leds, RGB_LED_COUNT, CRGB::Cyan);
            break;

        case RGBScene::UNLOCKING:
            sweep(CRGB::Green, true, 2.0f);
            break;

        case RGBScene::LOCKING:
            sweep(CRGB::Red, false, 2.0f);
            break;

        case RGBScene::IGNITION:
            // Amber fade in
            fill_solid(leds, RGB_LED_COUNT, CRGB(255,160,0));
            FastLED.setBrightness(currentBrightness * (0.5f + 0.5f * sin(animationPhase * 2.0f)));
            break;

        case RGBScene::STARTING:
            chase(CRGB::White, 5.0f);
            break;

        case RGBScene::ENGINE_RUNNING:
            // Slow green heartbeat
            breathe(CRGB::Green, 0.3f);
            break;

        case RGBScene::LOW_BATTERY:
            pulse(CRGB::Red, 0.5f);
            break;

        case RGBScene::OVERHEAT:
            pulse(CRGB::Orange, 0.8f);
            break;

        case RGBScene::ALARM:
            // Alternating Red/Blue
            if ((int)(animationPhase * 2) % 2 == 0) fill_solid(leds, RGB_LED_COUNT, CRGB::Red);
            else fill_solid(leds, RGB_LED_COUNT, CRGB::Blue);
            break;

        case RGBScene::OTA:
            // Rainbow progress
            fill_rainbow(leds, RGB_LED_COUNT, animationPhase * 10.0f, 255 / RGB_LED_COUNT);
            break;

        case RGBScene::FAULT:
            // Purple flash
            if ((int)(animationPhase * 5) % 2 == 0) fill_solid(leds, RGB_LED_COUNT, CRGB::Purple);
            else FastLED.clear();
            break;
    }

    // Restore default brightness if modified by specific scenes
    if (currentScene != RGBScene::IDLE && currentScene != RGBScene::IGNITION) {
        FastLED.setBrightness(currentBrightness);
    }
}

void RGBManager::updateHeartbeat()
{
    if (currentScene == RGBScene::ENGINE_RUNNING)
    {
        // la tiny brightness pulse every few seconds
        float hb = 0.98f + 0.02f * sin(millis() / 1000.0f * 0.5f);
        FastLED.setBrightness(currentBrightness * hb);
    }
}

void RGBManager::sweep(CRGB color, bool leftToRight, float speed)
{
    FastLED.clear();
    float pos = animationPhase * speed * RGB_LED_COUNT;
    int ledIdx = (int)pos % RGB_LED_COUNT;

    if (!leftToRight) ledIdx = (RGB_LED_COUNT - 1) - ledIdx;
    if (ledIdx >= 0 && ledIdx < RGB_LED_COUNT) leds[ledIdx] = color;
}

void RGBManager::breathe(CRGB color, float speed)
{
    float brightness = (sin(animationPhase * speed * 6.28f) + 1.0f) / 2.0f;
    fill_solid(leds, RGB_LED_COUNT, color);
    FastLED.setBrightness(currentBrightness * brightness);
}

void RGBManager::pulse(CRGB color, float speed)
{
    float brightness = (sin(animationPhase * speed * 3.14f) > 0) ? 1.0f : 0.2f;
    fill_solid(leds, RGB_LED_COUNT, color);
    FastLED.setBrightness(currentBrightness * brightness);
}

void RGBManager::chase(CRGB color, float speed)
{
    FastLED.clear();
    int ledIdx = (int)(animationPhase * speed * 10) % RGB_LED_COUNT;
    if (ledIdx >= 0 && ledIdx < RGB_LED_COUNT) leds[ledIdx] = color;
}
