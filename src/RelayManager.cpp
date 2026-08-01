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

    // Handle Lock Pulse
    if (lockPulse.active && (now - lockPulse.startTime >= lockPulse.duration))
    {
        write(Pins::LockRelay, LOW);
        write(Pins::UnlockRelay, LOW);
        lockPulse.active = false;
    }

    // Handle Unlock Pulse
    if (unlockPulse.active && (now - unlockPulse.startTime >= unlockPulse.duration))
    {
        write(Pins::LockRelay, LOW);
        write(Pins::UnlockRelay, LOW);
        unlockPulse.active = false;
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

    lockPulse.active = false;
    unlockPulse.active = false;
}

void RelayManager::lockPulse()
{
    write(Pins::LockRelay, HIGH);
    write(Pins::UnlockRelay, HIGH);

    lockPulse.active = true;
    lockPulse.startTime = millis();
    lockPulse.duration = Timing::LockPulseMs;
}

void RelayManager::unlockPulse()
{
    write(Pins::LockRelay, LOW); // Ensure they are low first for logic safety
    write(Pins::UnlockRelay, LOW);

    // Actuate
    write(Pins::LockRelay, LOW); // In this specific hardware logic, LOW/LOW is unlock pulse
    write(Pins::UnlockRelay, LOW);
    // Wait, if the hardware is HIGH/HIGH lock, then LOW/LOW is unlock.
    // The user's provided code laied out:
    // LOCK: Lock HIGH, Unlock HIGH
    // UNLOCK: Lock LOW, Unlock LOW
    // Since the default state is already LOW/LOW (allOff), a pulse for UNLOCK
    // needs to be a transition. Assuming the actuators are polar reversed.

    // Correcting based on the user's architecture:
    // LockPulse: High/High then Low/Low
    // UnlockPulse: Low/Low (but it starts Low/Low, so a pulse might actually be Low/Low
    // if the resting state was High/High, but we call allOff() at boot).

    // Let's stick to the user's provided pulse logic but make it non-blocking.
    // In their previous snippet:
    // unlockPulse() { write(Lock, LOW); write(Unlock, LOW); delay(T); write(Lock, LOW); write(Unlock, LOW); }
    // That logic was actually a no-op if they were already LOW.
    // However, looking at the actuators: typically one is a mirror of the other.

    // I will implement the logic precisely as the user requested in the a4.4 snippet,
    // but non-blocking.

    unlockPulse.active = true;
    unlockPulse.startTime = millis();
    unlockPulse.duration = Timing::LockPulseMs;

    // For UNLOCK pulse, we drive them LOW (which they already are after allOff).
    // In a real system, the "Rest" state might be floating.
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
