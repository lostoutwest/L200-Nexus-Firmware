#include "../include/VehicleState.h"

void VehicleState::reset()
{
    bleConnected = false;
    wifiConnected = false;

    locked = true;

    ignition = false;

    engineRunning = false;

    headlights = false;

    accessories = false;

    horn = false;

    batteryVoltage = 0.0f;

    coolantTemperature = 0.0f;

    oilPressure = 0.0f;

    rpm = 0;

    ambientLight = 0.0f;

    motionDetected = false;

    // Reset diagnostics to base values
    diagnostics.bootCount = 0;
    diagnostics.uptimeMs = 0;
    diagnostics.faultCount = 0;
}
