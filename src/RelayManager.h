#pragma once

#include <Arduino.h>

class RelayManager
{
public:

    void begin();

    void allOff();

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
};

extern RelayManager Relays;
