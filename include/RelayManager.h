#pragma once

#include <Arduino.h>

class RelayManager
{
public:

    void begin();

    void update();

    //--------------------------------------------------
    // Door Locks
    //--------------------------------------------------

    void lock();

    void unlock();

    //--------------------------------------------------
    // Ignition
    //--------------------------------------------------

    void ignitionOn();

    void ignitionOff();

    //--------------------------------------------------
    // Starter
    //--------------------------------------------------

    void starter();

    //--------------------------------------------------
    // Headlights
    //--------------------------------------------------

    void headlights(bool state);

    //--------------------------------------------------
    // Status
    //--------------------------------------------------

    bool lockPulseActive() const;

    bool unlockPulseActive() const;

    bool starterActive() const;

private:

    struct Pulse
    {
        bool active = false;

        uint8_t pin = 0;

        uint32_t startTime = 0;

        uint16_t duration = 0;
    };

    Pulse lockTimer;

    Pulse unlockTimer;

    Pulse starterTimer;

    //--------------------------------------------------

    void startPulse(
        Pulse& timer,
        uint8_t pin,
        uint16_t duration
    );

    void updatePulse(
        Pulse& timer
    );
};

extern RelayManager Relays;
