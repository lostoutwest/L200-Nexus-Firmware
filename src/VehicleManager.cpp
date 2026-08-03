#include "VehicleManager.h"
#include "VehicleState.h"
#include "RelayManager.h"
#include "Logger.h"

VehicleControllerManager VehicleController;

void VehicleControllerManager::begin()
{
    Log.info("Vehicle Manager Ready");
}

void VehicleControllerManager::update()
{
    // Future timers
    // Safety checks
    // Auto-lock
    // Starter timeout
}

bool VehicleControllerManager::lock()
{
    if (Vehicle.locked)
    {
        Log.debug("Already locked");
        return false;
    }

    Relays.lock();

    Vehicle.locked = true;

    Log.info("Vehicle Locked");

    return true;
}

bool VehicleControllerManager::unlock()
{
    if (!Vehicle.locked)
    {
        Log.debug("Already unlocked");
        return false;
    }

    Relays.unlock();

    Vehicle.locked = false;

    Log.info("Vehicle Unlocked");

    return true;
}

bool VehicleControllerManager::ignitionOn()
{
    if (Vehicle.ignition)
        return false;

    Relays.ignitionOn();

    Vehicle.ignition = true;

    Log.info("Ignition ON");

    return true;
}

bool VehicleControllerManager::ignitionOff()
{
    Relays.ignitionOff();

    Vehicle.ignition = false;

    Vehicle.engineRunning = false;

    Log.info("Ignition OFF");

    return true;
}

bool VehicleControllerManager::canStart() const
{
    if (!Vehicle.ignition)
        return false;

    if (Vehicle.engineRunning)
        return false;

    return true;
}

bool VehicleControllerManager::startEngine()
{
    if (!canStart())
    {
        Log.warning("Start request denied");
        return false;
    }

    Relays.starterOn();

    delay(800);

    Relays.starterOff();

    Vehicle.engineRunning = true;

    Log.info("Starter Engaged");

    return true;
}

bool VehicleControllerManager::stopStarter()
{
    Relays.starterOff();

    Log.info("Starter Released");

    return true;
}

bool VehicleControllerManager::headlights(bool state)
{
    Relays.headlights(state);

    Vehicle.headlights = state;

    Log.info(state ? "Headlights ON" : "Headlights OFF");

    return true;
}

bool VehicleControllerManager::accessories(bool state)
{
    Relays.accessories(state);

    Vehicle.accessories = state;

    Log.info(state ? "Accessories ON" : "Accessories OFF");

    return true;
}

bool VehicleControllerManager::horn(bool state)
{
    Relays.horn(state);

    Vehicle.horn = state;

    return true;
}
