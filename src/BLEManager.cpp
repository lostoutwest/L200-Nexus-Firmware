#include "BLEManager.h"
#include "VehicleManager.h"
#include "VehicleState.h"
#include "Logger.h"
#include "RGBManager.h"
#include "../include/config.h"

#include <ArduinoJson.h>

BLEManager BLE;

//====================================================
// Status JSON
//====================================================

static String statusJson()
{
    JsonDocument doc;

    doc["locked"]      = Vehicle.locked;
    doc["engine"]      = Vehicle.engineRunning;
    doc["ignition"]    = Vehicle.ignition;
    doc["headlights"]  = Vehicle.headlights;

    doc["battery"]     = Vehicle.batteryVoltage;
    doc["coolant"]     = Vehicle.coolantTemperature;

    doc["ble"]         = Vehicle.bleConnected;

    String output;

    serializeJson(doc, output);

    return output;
}

//====================================================
// Command Dispatcher
//====================================================

static bool handlePlainCommand(String command)
{
    command.trim();
    command.toUpperCase();

    Log.info("BLE CMD -> " + command);

    if (command == "PING")
    {
        BLE.notify("{\"pong\":true}");
        return true;
    }

    if (command == "STATUS")
    {
        BLE.notify(statusJson());
        return true;
    }

    if (command == "LOCK")
    {
        VehicleController.lock();
        BLE.notify(statusJson());
        return true;
    }

    if (command == "UNLOCK")
    {
        VehicleController.unlock();
        BLE.notify(statusJson());
        return true;
    }

    if (command == "IGNITION_ON")
    {
        VehicleController.ignitionOn();
        BLE.notify(statusJson());
        return true;
    }

    if (command == "IGNITION_OFF")
    {
        VehicleController.ignitionOff();
        BLE.notify(statusJson());
        return true;
    }

    if (command == "START_ENGINE")
    {
        VehicleController.startEngine();
        BLE.notify(statusJson());
        return true;
    }

    if (command == "HEADLIGHT_ON")
    {
        VehicleController.headlights(true);
        BLE.notify(statusJson());
        return true;
    }

    if (command == "HEADLIGHT_OFF")
    {
        VehicleController.headlights(false);
        BLE.notify(statusJson());
        return true;
    }

    Log.warning("BLE Unknown Command");

    BLE.notify("{\"ok\":false,\"msg\":\"unknown command\"}");

    return false;
}

//====================================================
// BLE Server Callbacks
//====================================================

class MyServerCallbacks : public NimBLEServerCallbacks
{
    void onConnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo) override
    {
        (void)pServer; // Unused parameter
        (void)connInfo; // Unused parameter

        Vehicle.bleConnected = true;

        Log.info("BLE Client Connected");

        Lighting.setScene(RGBScene::BLE_CONNECTED);

        BLE.notify(statusJson());
    }

    void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) override
    {
        (void)pServer; // Unused parameter
        (void)connInfo; // Unused parameter
        (void)reason; // Unused parameter

        Vehicle.bleConnected = false;

        Log.warning("BLE Client Disconnected");

        Lighting.setScene(RGBScene::IDLE);

        NimBLEAdvertising *advertising = NimBLEDevice::getAdvertising();

        advertising->stop();
        delay(50);
        advertising->start();

        Log.info("BLE Advertising Restarted");
    }
};

//====================================================
// Command Characteristic
//====================================================

class MyCommandCallbacks : public NimBLECharacteristicCallbacks
{
    void onWrite(NimBLECharacteristic *characteristic, NimBLEConnInfo& connInfo) override
    {
        Log.info("BLE Characteristic Write");
        (void)connInfo; // Unused parameter

        std::string value = characteristic->getValue();

        if (value.empty())
            return;

        String command = String(value.c_str());

        command.trim();

        Log.info("BLE RX -> " + command);

        // Plain text command first
        if (handlePlainCommand(command))
            return;

        // JSON command fallback
        JsonDocument doc;

        if (deserializeJson(doc, command))
        {
            Log.error("BLE JSON Parse Failed");
            return;
        }

        if (!doc["cmd"].is<String>())
        {
            Log.error("BLE Missing cmd");
            return;
        }

        String cmd = doc["cmd"];

        cmd.toUpperCase();

        handlePlainCommand(cmd);
    }
};

//====================================================
// RGB Characteristic
//====================================================

class MyRGBCallbacks : public NimBLECharacteristicCallbacks
{
    void onWrite(NimBLECharacteristic *characteristic, NimBLEConnInfo& connInfo) override
    {
        (void)connInfo; // Unused parameter

        std::string value = characteristic->getValue();

        if (value.empty())
            return;

        String payload = value.c_str();

        payload.trim();

        Log.info("RGB RX -> " + payload);

        JsonDocument doc;

        if (deserializeJson(doc, payload))
        {
            Log.error("RGB JSON Parse Failed");
            return;
        }

        if (doc["brightness"].is<int>())
        {
            Lighting.setBrightness(doc["brightness"]);
        }

        if (doc["scene"].is<String>())
        {
            String scene = doc["scene"];

            scene.toUpperCase();

            if (scene == "BOOT")
                Lighting.setScene(RGBScene::BOOT);

            else if (scene == "IDLE")
                Lighting.setScene(RGBScene::IDLE);

            else if (scene == "CONNECTED")
                Lighting.setScene(RGBScene::BLE_CONNECTED);

            else if (scene == "LOCK")
                Lighting.setScene(RGBScene::LOCKING);

            else if (scene == "UNLOCK")
                Lighting.setScene(RGBScene::UNLOCKING);

            else if (scene == "ENGINE")
                Lighting.setScene(RGBScene::ENGINE_RUNNING);

            else if (scene == "FAULT")
                Lighting.setScene(RGBScene::FAULT);
        }

        BLE.notify("{\"ok\":true}");
    }
};

//====================================================
// Config Characteristic
//====================================================

class MyConfigCallbacks : public NimBLECharacteristicCallbacks
{
    void onWrite(NimBLECharacteristic *characteristic, NimBLEConnInfo& connInfo) override
    {
        (void)connInfo; // Unused parameter

        std::string value = characteristic->getValue();

        if (value.empty())
            return;

        Log.info("Config Updated");

        BLE.notify("{\"ok\":true}");
    }
};

//====================================================
// OTA Characteristic
//====================================================

class MyOTACallbacks : public NimBLECharacteristicCallbacks
{
    void onWrite(NimBLECharacteristic *characteristic, NimBLEConnInfo& connInfo) override
    {
        (void)characteristic; // Unused parameter - used for compatibility
        (void)connInfo; // Unused parameter

        std::string value = characteristic->getValue();

        if (value.empty())
            return;

        Log.info("OTA Request Received");

        Lighting.setScene(RGBScene::OTA);

        BLE.notify("{\"ok\":true,\"msg\":\"OTA\"}");
    }
};

//====================================================
// BLE Manager
//====================================================

void BLEManager::begin()
{
    Log.info("***** BLEManager.cpp BUILD 7 *****");

    NimBLEDevice::init(DEVICE_NAME);

    NimBLEDevice::setPower(ESP_PWR_LVL_P9);

    server = NimBLEDevice::createServer();
    server->setCallbacks(new MyServerCallbacks());

    Log.info("BLE: Creating Service...");

    NimBLEUUID serviceUUID(SERVICE_UUID);
    service = server->createService(serviceUUID);

    if (service == nullptr)
    {
        Log.error("FAILED TO CREATE SERVICE");
        return;
    }

    Log.info("CUSTOM SERVICE CREATED");
    Log.info("Service pointer:");
    Serial.println((uintptr_t)service, HEX);

    Log.info("SERVICE UUID:");
    Log.info(SERVICE_UUID);

    //--------------------------------------------------
    // Command Characteristic
    //--------------------------------------------------

    commandChar = service->createCharacteristic(
        NimBLEUUID(COMMAND_UUID),
        NIMBLE_PROPERTY::WRITE |
        NIMBLE_PROPERTY::WRITE_NR
    );

    commandChar->setCallbacks(new MyCommandCallbacks());

    if (commandChar == nullptr)
        Log.error("COMMAND CHAR FAILED");
    else {
        Log.info("Command pointer:");
        Serial.println((uintptr_t)commandChar, HEX);
    }

    //--------------------------------------------------
    // Status Characteristic
    //--------------------------------------------------

    statusChar = service->createCharacteristic(
        NimBLEUUID(STATUS_UUID),
        NIMBLE_PROPERTY::READ |
        NIMBLE_PROPERTY::NOTIFY
    );

    statusChar->createDescriptor(
        "2902",
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE
    );

    if (statusChar == nullptr)
        Log.error("STATUS CHAR FAILED");
    else {
        Log.info("Status pointer:");
        Serial.println((uintptr_t)statusChar, HEX);
    }

    //--------------------------------------------------
    // RGB Characteristic
    //--------------------------------------------------

    rgbChar = service->createCharacteristic(
        RGB_UUID,
        NIMBLE_PROPERTY::WRITE
    );

    rgbChar->setCallbacks(new MyRGBCallbacks());

    //--------------------------------------------------
    // Configuration Characteristic
    //--------------------------------------------------

    configChar = service->createCharacteristic(
        CONFIGURATION_UUID,
        NIMBLE_PROPERTY::READ |
        NIMBLE_PROPERTY::WRITE
    );

    configChar->setCallbacks(new MyConfigCallbacks());

    //--------------------------------------------------
    // OTA Characteristic
    //--------------------------------------------------

    otaChar = service->createCharacteristic(
        OTA_UUID,
        NIMBLE_PROPERTY::WRITE
    );

    otaChar->setCallbacks(new MyOTACallbacks());

    //--------------------------------------------------
    // Start Service
    //--------------------------------------------------

    service->start();
    server->start();
    server->advertiseOnDisconnect(true);
    Log.info("SERVICE START CALLED");

    Log.info("BLE: Service Ready");
    statusChar->setValue("{\"boot\":true}");

    //--------------------------------------------------
    // Advertising
    //--------------------------------------------------

    NimBLEAdvertising *advertising = NimBLEDevice::getAdvertising();

    NimBLEAdvertisementData advData;
    NimBLEAdvertisementData scanData;

    advData.setName(DEVICE_NAME);
    advData.addServiceUUID(NimBLEUUID(SERVICE_UUID));
    advData.setPreferredParams(0x06, 0x20);

    scanData.setName(DEVICE_NAME);
    scanData.addServiceUUID(NimBLEUUID(SERVICE_UUID));

    advertising->setAdvertisementData(advData);
    advertising->setScanResponseData(scanData);
    advertising->enableScanResponse(true);

    Log.info("BLE: Starting Advertising...");

    if (advertising->start())
    {
        Log.info("BLE: Advertising Started");
    }
    else
    {
        Log.error("BLE: Advertising FAILED");
    }

    Lighting.setScene(RGBScene::IDLE);

    Log.info("----------------------------------");
    Log.info("BLE READY");
    Log.info("----------------------------------");
}

void BLEManager::update()
{
    // Event driven
}

bool BLEManager::connected() const
{
    return Vehicle.bleConnected;
}

void BLEManager::notify(const String& message)
{
    if (!statusChar)
        return;

    if (!Vehicle.bleConnected)
        return;

    statusChar->setValue(message.c_str());

    statusChar->notify();
}