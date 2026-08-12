#include "../include/RelayManager.h"
#include "../include/Config.h"

RelayManager Relays;

//====================================================
// Initialisation
//====================================================

void RelayManager::begin()
{
    pinMode(PIN_LOCK_RELAY, OUTPUT);
    pinMode(PIN_UNLOCK_RELAY, OUTPUT);
    pinMode(PIN_IGNITION_RELAY, OUTPUT);
    pinMode(PIN_STARTER_RELAY, OUTPUT);
    pinMode(PIN_HEADLIGHT_RELAY, OUTPUT);

    digitalWrite(PIN_LOCK_RELAY, HIGH);
    digitalWrite(PIN_UNLOCK_RELAY, HIGH);
    digitalWrite(PIN_IGNITION_RELAY, HIGH);
    digitalWrite(PIN_STARTER_RELAY, HIGH);
    digitalWrite(PIN_HEADLIGHT_RELAY, HIGH);
}

//====================================================
// Main Update
//====================================================

void RelayManager::update()
{
    updatePulse(lockTimer);
    updatePulse(unlockTimer);
    updatePulse(starterTimer);
}

//====================================================
// Pulse Engine
//====================================================

void RelayManager::startPulse(
    Pulse& timer,
    uint8_t pin,
    uint16_t duration)
{
    digitalWrite(pin, LOW);

    timer.active = true;
    timer.pin = pin;
    timer.duration = duration;
    timer.startTime = millis();
}

void RelayManager::updatePulse(Pulse& timer)
{
    if (!timer.active)
        return;

    if ((millis() - timer.startTime) >= timer.duration)
    {
        digitalWrite(timer.pin, HIGH);

        timer.active = false;
    }
}

//====================================================
// Lock
//====================================================

void RelayManager::lock()
{
    // Use non-blocking pulse for lock
    if (lockTimer.active)
        return;

    startPulse(
        lockTimer,
        PIN_LOCK_RELAY,
        LOCK_PULSE_TIME
    );
}

//====================================================
// Unlock
//====================================================

void RelayManager::unlock()
{
    if (unlockTimer.active)
        return;

    startPulse(
        unlockTimer,
        PIN_UNLOCK_RELAY,
        UNLOCK_PULSE_TIME
    );
}

//====================================================
// Ignition
//====================================================

void RelayManager::ignitionOn()
{
    digitalWrite(
        PIN_IGNITION_RELAY,
        LOW
    );
}

void RelayManager::ignitionOff()
{
    digitalWrite(
        PIN_IGNITION_RELAY,
        HIGH
    );
}

//====================================================
// Starter
//====================================================

void RelayManager::starter()
{
    if (starterTimer.active)
        return;

    startPulse(
        starterTimer,
        PIN_STARTER_RELAY,
        STARTER_TIME
    );
}

//====================================================
// Headlights
//====================================================

void RelayManager::headlights(bool state)
{
    digitalWrite(
        PIN_HEADLIGHT_RELAY,
        !state
    );
}

//====================================================
// Status
//====================================================

bool RelayManager::lockPulseActive() const
{
    return lockTimer.active;
}

bool RelayManager::unlockPulseActive() const
{
    return unlockTimer.active;
}

bool RelayManager::starterActive() const
{
    return starterTimer.active;
}
