#include "VehicleManager.h"
#include "VehicleState.h"
#include "RelayManager.h"
#include "Logger.h"

VehicleManager VehicleMgr;

void VehicleManager::begin()
{
    // Initialize the low-level relay hardware
    Relays.begin();

    // Sync state to initial hardware state
    Vehicle.locked = true;
    Relays.lock();

    Log.info("Vehicle Manager Started");
}

void VehicleManager::update()
{
    // Monitoring logic and safety checks can go here
}

void VehicleManager::requestUnlock()
{
    Log.info("Request: UNLOCK");

    Relays.unlock();
    Vehicle.locked = false;

    Log.info("Vehicle Unlocked");
}

void VehicleManager::requestLock()
{
    Log.info("Request: LOCK");

    Relays.lock();
    Vehicle.locked = true;

    Log.info("Vehicle Locked");
}

void VehicleManager::requestIgnition(bool state)
{
    Log.info(state ? "Request: IGNITION ON" : "Request: IGNITION OFF");

    Relays.ignition(state);
    Vehicle.ignition = state;

    Log.info(state ? "Ignition Active" : "Ignition Disabled");
}

void VehicleManager::requestHeadlights(bool state)
{
    Log.info(state ? "Request: HEADLIGHTS ON" : "Request: HEADLIGHTS OFF");

    Relays.headlights(state);
    Vehicle.headlights = state;

    Log.info(state ? "Headlights Active" : "Headlights Disabled");
}
