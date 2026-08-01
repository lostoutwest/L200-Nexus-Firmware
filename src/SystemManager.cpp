#include <Arduino.h>

#include "SystemManager.h"
#include "Logger.h"
#include "VehicleManager.h"
#include "RGBManager.h"

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

    RGB.begin();
    RGB.setScene(RGBScene::BOOT);

    VehicleMgr.begin();

    Log.info("System Ready");
    RGB.setScene(RGBScene::IDLE);
}

void SystemManager::update()
{
    if (!initialised)
        return;

    VehicleMgr.update();
    RGB.update();
}
