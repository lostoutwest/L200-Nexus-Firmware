#include <Arduino.h>

#include "SystemManager.h"
#include "Logger.h"
#include "VehicleManager.h"

#include "../include/config.h"
#include "../include/version.h"

void SystemManager::begin()
{
    Serial.begin(SERIAL_BAUD);

    delay(50);

    Log.begin();

    Log.banner();

    Log.info("System Manager Started");

    Log.info("Initialising...");

    VehicleMgr.begin();

    Log.info("System Ready");
}

void SystemManager::update()
{
    if (!initialised)
        return;

    VehicleMgr.update();
}
