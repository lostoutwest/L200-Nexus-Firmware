#include <Arduino.h>

#include "SystemManager.h"
#include "Logger.h"
#include "VehicleManager.h"
#include "RGBManager.h"
#include "BLEManager.h"
#include "WiFiManager.h"
#include "SensorManager.h"
#include "FaultManager.h"
#include "OTAManager.h"
#include "SecurityManager.h"

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

    // Core Modules
    RGB.begin();
    RGB.setScene(RGBScene::BOOT);

    VehicleMgr.begin();

    // Interface Modules
    BLE.begin();
    WiFi.begin();

    // Utility Modules
    Sensors.begin();
    Faults.begin();
    OTA.begin();
    Security.begin();

    Log.info("System Ready");
    RGB.setScene(RGBScene::IDLE);
}

void SystemManager::update()
{
    if (!initialised)
        return;

    VehicleMgr.update();
    RGB.update();
    Relays.update();
    BLE.update();
    WiFi.update();
    Sensors.update();
    Faults.update();
    OTA.update();
    Security.update();
}
