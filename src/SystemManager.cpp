#include <Arduino.h>

#include "../include/SystemManager.h"
#include "../include/RelayManager.h"
#include "../include/Logger.h"
#include "../include/VehicleController.h"
#include "../include/RGBManager.h"
#include "../include/BLEManager.h"
#include "../include/WiFiManager.h"
#include "../include/FaultManager.h"
#include "../include/OTAManager.h"
#include "../include/SecurityManager.h"

#include "../include/Config.h"

SystemManager System;

void SystemManager::begin()
{
    Serial.begin(115200);

    delay(50);

    Log.begin();

    Log.banner();

    Log.info("System Manager Started");

    Log.info("Initialising...");

    // Core Modules
    Lighting.begin();
    Lighting.setScene(RGBScene::BOOT);

    Vehicle.begin();

    // Interface Modules
    BLE.begin();
    WiFiInterface.begin();

    // Utility Modules
    Sensors.begin();
    Faults.begin();
    OTA.begin();
    Security.begin();

    Log.info("System Ready");
    Lighting.setScene(RGBScene::IDLE);
    initialised = true;
}

void SystemManager::update()
{
    if (!initialised)
        return;

    Vehicle.update();
    Lighting.update();
    Relays.update();
    BLE.update();
    WiFiInterface.update();
    Sensors.update();
    Faults.update();
    OTA.update();
    Security.update();
}
