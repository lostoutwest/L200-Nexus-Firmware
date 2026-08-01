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

void RelayManager::update()
{
    uint32_t now = millis();

    for (auto &p : pulses)
    {
        if (!p.active)
            continue;

        if (now - p.startTime >= p.duration)
        {
            digitalWrite(p.pin, p.endState);
            p.active = false;
        }
    }
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

    for (auto &p : pulses)
    {
        p.active = false;
    }
}

void RelayManager::pulse(uint8_t pin, bool startState, bool endState, uint16_t duration)
{
    // Find first available pulse slot
    for (auto &p : pulses)
    {
        if (!p.active)
        {
            digitalWrite(pin, startState);
            p.pin = pin;
            p.active = true;
            p.startTime = millis();
            p.duration = duration;
            p.endState = endState;
            return;
        }
    }
    // If we reach here, all 8 slots are full (extremely unlikely)
}

void RelayManager::lockPulse()
{
    // Lock logic: Both HIGH then both LOW
    pulse(Pins::LockRelay, HIGH, LOW, Timing::LockPulseMs);
    pulse(Pins::UnlockRelay, HIGH, LOW, Timing::LockPulseMs);
}

void RelayManager::unlockPulse()
{
    // Unlock logic: Both LOW then both LOW (per user spec)
    // Note: In a typical system this would be a polarity flip,
    // but we follow the provided spec exactly.
    pulse(Pins::LockRelay, LOW, LOW, Timing::LockPulseMs);
    pulse(Pins::UnlockRelay, LOW, LOW, Timing::LockPulseMs);
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
