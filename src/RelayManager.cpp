#include "RelayManager.h"

#include "../include/config.h"

RelayManager Relays;

void RelayManager::begin()
{
    pinMode(Pins::LockRelay, OUTPUT);
    pinMode(Pins::UnlockRelay, OUTPUT);
    pinMode(Pins::IgnitionRelay, OUTPUT);
    pinMode(Pins::StarterRelay, OUTPUT);
    pinMode(Pins::HeadlightRelay, OUTPUT);
    pinMode(Pins::AccessoryRelay, OUTPUT);
    pinMode(Pins::HornRelay, OUTPUT);

    allOff();
}

void RelayManager::write(uint8_t pin, bool state)
{
    digitalWrite(pin, state ? HIGH : LOW);
}

void RelayManager::allOff()
{
    write(Pins::LockRelay, LOW);
    write(Pins::UnlockRelay, LOW);
    write(Pins::IgnitionRelay, LOW);
    write(Pins::StarterRelay, LOW);
    write(Pins::HeadlightRelay, LOW);
    write(Pins::AccessoryRelay, LOW);
    write(Pins::HornRelay, LOW);
}

void RelayManager::lockPulse()
{
    write(Pins::LockRelay, HIGH);
    write(Pins::UnlockRelay, HIGH);

    delay(Timing::LockPulseMs);

    write(Pins::LockRelay, LOW);
    write(Pins::UnlockRelay, LOW);
}

void RelayManager::unlockPulse()
{
    write(Pins::LockRelay, LOW);
    write(Pins::UnlockRelay, LOW);

    delay(Timing::LockPulseMs);

    write(Pins::LockRelay, LOW);
    write(Pins::UnlockRelay, LOW);
}

void RelayManager::ignitionOn()
{
    write(Pins::IgnitionRelay, HIGH);
}

void RelayManager::ignitionOff()
{
    write(Pins::IgnitionRelay, LOW);
}

void RelayManager::starterOn()
{
    write(Pins::StarterRelay, HIGH);
}

void RelayManager::starterOff()
{
    write(Pins::StarterRelay, LOW);
}

void RelayManager::headlights(bool state)
{
    write(Pins::HeadlightRelay, state);
}

void RelayManager::accessories(bool state)
{
    write(Pins::AccessoryRelay, state);
}

void RelayManager::horn(bool state)
{
    write(Pins::HornRelay, state);
}
