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
    pinMode(PIN_RELAY_ACCESSORIES, OUTPUT);
    pinMode(PIN_RELAY_HORN, OUTPUT);

    // Safe default: Locked, All Off
    lock();
    ignitionOff();
    stopStarter();
    headlights(false);
    accessories(false);
    horn(false);
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

void RelayManager::ignitionOn()
{
    digitalWrite(PIN_RELAY_IGNITION, HIGH);
}

void RelayManager::ignitionOff()
{
    digitalWrite(PIN_RELAY_IGNITION, LOW);
}

void RelayManager::startEngine()
{
    digitalWrite(PIN_RELAY_STARTER, HIGH);
}

void RelayManager::stopStarter()
{
    digitalWrite(PIN_RELAY_STARTER, LOW);
}

void RelayManager::headlights(bool state)
{
    digitalWrite(PIN_RELAY_HEADLIGHTS, state ? HIGH : LOW);
}

void RelayManager::accessories(bool state)
{
    digitalWrite(PIN_RELAY_ACCESSORIES, state ? HIGH : LOW);
}

void RelayManager::horn(bool state)
{
    digitalWrite(PIN_RELAY_HORN, state ? HIGH : LOW);
}
