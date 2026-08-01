#include "RelayManager.h"
#include <Arduino.h>
#include "../include/config.h"

RelayManager Relays;

void RelayManager::begin()
{
    pinMode(PIN_RELAY_LOCK_A, OUTPUT);
    pinMode(PIN_RELAY_LOCK_B, OUTPUT);
    pinMode(PIN_RELAY_IGNITION, OUTPUT);
    pinMode(PIN_RELAY_STARTER, OUTPUT);
    pinMode(PIN_RELAY_HEADLIGHTS, OUTPUT);

    // Default state: Locked
    lock();
}

void RelayManager::lock()
{
    digitalWrite(PIN_RELAY_LOCK_A, HIGH);
    digitalWrite(PIN_RELAY_LOCK_B, HIGH);
}

void RelayManager::unlock()
{
    digitalWrite(PIN_RELAY_LOCK_A, LOW);
    digitalWrite(PIN_RELAY_LOCK_B, LOW);
}

void RelayManager::ignition(bool state)
{
    digitalWrite(PIN_RELAY_IGNITION, state ? HIGH : LOW);
}

void RelayManager::starter(bool state)
{
    digitalWrite(PIN_RELAY_STARTER, state ? HIGH : LOW);
}

void RelayManager::headlights(bool state)
{
    digitalWrite(PIN_RELAY_HEADLIGHTS, state ? HIGH : LOW);
}
