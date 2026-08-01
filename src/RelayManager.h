#pragma once

#include <Arduino.h>

class RelayManager
{
public:
    void begin();

    void lock();
    void unlock();
    void ignition(bool state);
    void starter(bool state);
    void headlights(bool state);
};

extern RelayManager Relays;
