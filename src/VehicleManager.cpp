#include "VehicleManager.h"

#include "VehicleState.h"
#include "RelayManager.h"

#include "../Services/Logger.h"

VehicleManager VehicleController;

void VehicleManager::begin()
{
    Log.info("Vehicle Manager Ready");
}

void VehicleManager::update()
{
    // Future timers
    // Safety checks
    // Auto-lock
    // Starter timeout
}

bool VehicleManager::lock()
{
    if (Vehicle.locked)
    {
        Log.debug("Already locked");
        return false;
    }

    Relays.lockPulse();

    Vehicle.locked = true;

    Log.info("Vehicle Locked");

    return true;
}

bool VehicleManager::unlock()
{
    if (!Vehicle.locked)
    {
        Log.debug("Already unlocked");
        return false;
    }

    Relays.unlockPulse();

    Vehicle.locked = false;

    Log.info("Vehicle Unlocked");

    return true;
}

bool VehicleManager::ignitionOn()
{
    if (Vehicle.ignition)
        return false;

    Relays.ignitionOn();

    Vehicle.ignition = true;

    Log.info("Ignition ON");

    return true;
}

bool VehicleManager::ignitionOff()
{
    Relays.ignitionOff();

    Vehicle.ignition = false;

    Vehicle.engineRunning = false;

    Log.info("Ignition OFF");

    return true;
}

bool VehicleManager::canStart() const
{
    if (!Vehicle.ignition)
        return false;

    if (Vehicle.engineRunning)
        return false;

    return true;
}

bool VehicleManager::startEngine()
{
    if (!canStart())
    {
        Log.warning("Start request denied");
        return false;
    }

    Relays.starterOn();

    Log.info("Starter Engaged");

    return true;
}

bool VehicleManager::stopStarter()
{
    Relays.starterOff();

    Log.info("Starter Released");

    return true;
}

bool VehicleManager::headlights(bool state)
{
    Relays.headlights(state);

    Vehicle.headlights = state;

    Log.info(state ? "Headlights ON" : "Headlights OFF");

    return true;
}

bool VehicleManager::accessories(bool state)
{
    Relays.accessories(state);

    Vehicle.accessories = state;

    Log.info(state ? "Accessories ON" : "Accessories OFF");

    return true;
}

bool VehicleManager::horn(bool state)
{
    Relays.horn(state);

    Vehicle.horn = state;

    return true;
}
