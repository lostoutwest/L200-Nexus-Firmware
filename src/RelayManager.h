#pragma once

#include <Arduino.h>

struct RelayPulse
{
    bool active = false;
    uint8_t pin = 0;
    bool endState = LOW;
    uint32_t startTime = 0;
    uint16_t duration = 0;
};

class RelayManager
{
public:

    void begin();

    void update();

    void allOff();

    void lock();

    void unlock();

    void lockPulse();

    void unlockPulse();

    void ignitionOn();

    void ignitionOff();

    void starterOn();

    void starterOff();

    void headlights(bool state);

    void accessories(bool state);

    void horn(bool state);

private:

    void write(uint8_t pin, bool state);

    void pulse(uint8_t pin, bool startState, bool endState, uint16_t duration);

    RelayPulse pulses[8];
};

extern RelayManager Relays;
