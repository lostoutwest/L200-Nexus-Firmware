#include "VehicleManager.h"
#include "VehicleState.h"
#include "RelayManager.h"
#include "Logger.h"

VehicleManager VehicleMgr;

void VehicleManager::begin()
{
    Relays.begin();

    // Sync state to initial hardware state
    Vehicle.locked = true;
    Relays.lock();

    Log.info("Vehicle Manager Started");
}

void VehicleManager::update()
{
    // Future safety monitoring logic here
}

void VehicleManager::lock()
{
    if (Vehicle.locked) {
        Log.warning("Lock request ignored - vehicle already locked");
        return;
    }

    Relays.lock();
    Vehicle.locked = true;
    Log.info("Vehicle Locked");
}

void VehicleManager::unlock()
{
    if (!Vehicle.locked) {
        Log.warning("Unlock request ignored - vehicle already unlocked");
        return;
    }

    Relays.unlock();
    Vehicle.locked = false;
    Log.info("Vehicle Unlocked");
}

void VehicleManager::startEngine()
{
    if (Vehicle.engineRunning) {
        Log.warning("Start request ignored - engine already running");
        return;
    }

    Log.info("Request: START ENGINE");

    Relays.ignitionOn();
    Vehicle.ignition = true;

    delay(200); // Stabilization

    Relays.startEngine();
    Log.info("Cranking...");

    // Simulate a 1-second crank as we await real RPM input logic
    delay(1000);

    Relays.stopStarter();
    Vehicle.engineRunning = true;

    Log.info("Engine Started");
}

void VehicleManager::stopEngine()
{
    if (!Vehicle.engineRunning) {
        Log.warning("Stop request ignored - engine not running");
        return;
    }

    Relays.ignitionOff();
    Vehicle.ignition = false;
    Vehicle.engineRunning = false;

    Log.info("Engine Stopped");
}

void VehicleManager::headlights(bool state)
{
    if (Vehicle.headlights == state) {
        Log.warning("Headlight request ignored - state already " + String(state ? "ON" : "OFF"));
        return;
    }

    Relays.headlights(state);
    Vehicle.headlights = state;
    Log.info(state ? "Headlights ON" : "Headlights OFF");
}

void VehicleManager::accessories(bool state)
{
    if (Vehicle.accessories == state) {
        Log.warning("Accessories request ignored - state already " + String(state ? "ON" : "OFF"));
        return;
    }

    Relays.accessories(state);
    Vehicle.accessories = state;
    Log.info(state ? "Accessories ON" : "Accessories OFF");
}
