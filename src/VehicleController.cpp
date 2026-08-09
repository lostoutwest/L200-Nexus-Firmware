#include "../include/VehicleController.h"
#include "VehicleEvent.h"

#include "../include/RelayManager.h"
#include "../include/RGBManager.h"

#include <ArduinoJson.h>

VehicleController Vehicle;

//=====================================================
// Startup
//=====================================================

void VehicleController::begin()
{
    vehicle.locked = true;
    vehicle.ignition = false;
    vehicle.engineRunning = false;
    vehicle.headlights = false;
    vehicle.bleConnected = false;

    vehicle.batteryVoltage = 12.6f;
    vehicle.coolantTemperature = 20.0f;
}

//=====================================================

void VehicleController::update()
{
    // Future:
    // Battery monitor
    // Engine running detection
    // Door switches
    // Ignition sense
}

//=====================================================
// LOCK
//=====================================================

VehicleEvent VehicleController::lock()
{
    Relays.lock();

    vehicle.locked = true;

    return VehicleEvent::LOCKED;
}

//=====================================================
// UNLOCK
//=====================================================

VehicleEvent VehicleController::unlock()
{
    Relays.unlock();

    vehicle.locked = false;

    return VehicleEvent::UNLOCKED;
}

//=====================================================
// IGNITION
//=====================================================

VehicleEvent VehicleController::ignitionOn()
{
    if(vehicle.ignition)
        return VehicleEvent::NONE;

    Relays.ignitionOn();

    vehicle.ignition = true;

    return VehicleEvent::IGNITION_ON;
}

VehicleEvent VehicleController::ignitionOff()
{
    if(!vehicle.ignition)
        return VehicleEvent::NONE;

    Relays.ignitionOff();

    vehicle.ignition = false;
    vehicle.engineRunning = false; // Engine stops when ignition is turned off

    return VehicleEvent::IGNITION_OFF;
}

//=====================================================
// STARTER
//=====================================================

VehicleEvent VehicleController::startEngine()
{
    if(!vehicle.ignition)
        return VehicleEvent::NONE;

    if(vehicle.engineRunning)
        return VehicleEvent::NONE;

    if(Relays.starterActive())
        return VehicleEvent::NONE;

    Relays.starter();

    vehicle.engineRunning = true; // Assuming success for now

    return VehicleEvent::ENGINE_STARTED;
}

VehicleEvent VehicleController::stopEngine()
{
    ignitionOff();

    return VehicleEvent::ENGINE_STOPPED;
}

//=====================================================
// HEADLIGHTS
//=====================================================

VehicleEvent VehicleController::headlights(bool state)
{
    Relays.headlights(state);

    vehicle.headlights = state;

    return state ? VehicleEvent::HEADLIGHTS_ON : VehicleEvent::HEADLIGHTS_OFF;
}

//=====================================================
// BLE
//=====================================================

void VehicleController::setBLEConnected(bool state)
{
    vehicle.bleConnected = state;
}

bool VehicleController::bleConnected() const
{
    return vehicle.bleConnected;
}

//=====================================================
// STATE
//=====================================================

VehicleState& VehicleController::state()
{
    return vehicle;
}

//=====================================================
// JSON
//=====================================================

String VehicleController::json()
{
    JsonDocument doc;

    doc["locked"] = vehicle.locked;
    doc["ignition"] = vehicle.ignition;
    doc["engine"] = vehicle.engineRunning;
    doc["headlights"] = vehicle.headlights;
    doc["battery"] = vehicle.batteryVoltage;
    doc["coolant"] = vehicle.coolantTemperature;
    doc["ble"] = vehicle.bleConnected;

    String output;

    serializeJson(doc, output);

    return output;
}
