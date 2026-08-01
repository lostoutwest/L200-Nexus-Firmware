#pragma once

#include <Arduino.h>

class RelayManager
{
public:
    void begin();

    void lock();
    void unlock();

    void ignitionOn();
    void ignitionOff();

    void startEngine();
    void stopStarter();

    void headlights(bool state);
    void accessories(bool state);
    void horn(bool state);
};

extern RelayManager Relays;
