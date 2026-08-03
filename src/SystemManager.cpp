#include <Arduino.h>

#include "SystemManager.h"
#include "RelayManager.h"
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
    Lighting.begin();
    Lighting.setScene(RGBScene::BOOT);

    VehicleController.begin();

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

    VehicleController.update();
    Lighting.update();
    Relays.update();
    BLE.update();
    WiFiInterface.update();
    Sensors.update();
    Faults.update();
    OTA.update();
    Security.update();
}
