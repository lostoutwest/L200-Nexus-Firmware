#pragma once

#include <Arduino.h>
#include "VehicleState.h"
#include "VehicleEvent.h"

class VehicleController
{
public:

    void begin();

    void update();

    //-------------------------------------------------
    // Vehicle Functions
    //-------------------------------------------------

    VehicleEvent lock();

    VehicleEvent unlock();

    VehicleEvent ignitionOn();

    VehicleEvent ignitionOff();

    VehicleEvent startEngine();

    VehicleEvent stopEngine();

    VehicleEvent headlights(bool state);

    //-------------------------------------------------
    // BLE
    //-------------------------------------------------

    void setBLEConnected(bool state);

    bool bleConnected() const;

    //-------------------------------------------------
    // Status
    //-------------------------------------------------

    VehicleState& state();

    String json();

private:

    VehicleState vehicle;
};

extern VehicleController Vehicle;