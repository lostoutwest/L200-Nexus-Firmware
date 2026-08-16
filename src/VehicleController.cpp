#include "../include/VehicleController.h"
#include "../include/VehicleEvent.h"
#include "../include/RelayManager.h"
#include "../include/RGBManager.h"
#include <ArduinoJson.h>

VehicleController Vehicle;

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

void VehicleController::update() {}

VehicleEvent VehicleController::lock()
{
    Relays.lock();
    vehicle.locked = true;
    return VehicleEvent::LOCKED;
}

VehicleEvent VehicleController::unlock()
{
    Relays.unlock();
    vehicle.locked = false;
    vehicle.tamperDetected = false;
    return VehicleEvent::UNLOCKED;
}

VehicleEvent VehicleController::ignitionOn()
{
    if (vehicle.ignition) return VehicleEvent::NONE;
    Relays.ignitionOn();
    vehicle.ignition = true;
    return VehicleEvent::IGNITION_ON;
}

VehicleEvent VehicleController::ignitionOff()
{
    if (!vehicle.ignition) return VehicleEvent::NONE;
    Relays.ignitionOff();
    vehicle.ignition = false;
    vehicle.engineRunning = false;
    return VehicleEvent::IGNITION_OFF;
}

VehicleEvent VehicleController::startEngine()
{
    if (!vehicle.ignition || vehicle.engineRunning || Relays.starterActive())
        return VehicleEvent::NONE;
    Relays.starter();
    vehicle.engineRunning = true;
    return VehicleEvent::ENGINE_STARTED;
}

VehicleEvent VehicleController::stopEngine()
{
    ignitionOff();
    return VehicleEvent::ENGINE_STOPPED;
}

VehicleEvent VehicleController::headlights(bool state)
{
    Relays.headlights(state);
    vehicle.headlights = state;
    return state ? VehicleEvent::HEADLIGHTS_ON : VehicleEvent::HEADLIGHTS_OFF;
}

void VehicleController::setBLEConnected(bool state) { vehicle.bleConnected = state; }
bool VehicleController::bleConnected() const { return vehicle.bleConnected; }
VehicleState& VehicleController::state() { return vehicle; }

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
    doc["motionDetected"] = vehicle.motionDetected;
    doc["accelX"] = vehicle.accelX;
    doc["accelY"] = vehicle.accelY;
    doc["accelZ"] = vehicle.accelZ;
    doc["pitch"] = vehicle.pitch;
    doc["roll"] = vehicle.roll;
    doc["tiltDetected"] = vehicle.tiltDetected;
    doc["tamperDetected"] = vehicle.tamperDetected;
    doc["sensorMode"] = vehicle.sensorMode == 0 ? "LOCKED" : vehicle.sensorMode == 1 ? "UNLOCKED" : "DRIVING";
    String output;
    serializeJson(doc, output);
    return output;
}
