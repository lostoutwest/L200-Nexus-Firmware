#include "BLEManager.h"
#include "VehicleManager.h"
#include "VehicleState.h"
#include "Logger.h"
#include "RGBManager.h"
#include "../include/config.h"
#include <ArduinoJson.h>

BLEManager BLE;

class MyServerCallbacks : public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* pServer) {
        Vehicle.bleConnected = true;
        Log.info("BLE: Client Connected");
        RGB.setScene(RGBScene::BLE_CONNECTED);
    }

    void onDisconnect(NimBLEServer* pServer) {
        Vehicle.bleConnected = false;
        Log.info("BLE: Client Disconnected");
        RGB.setScene(RGBScene::IDLE);
        // Start advertising again
        NimBLEDevice::startAdvertising();
    }
};

class MyCommandCallbacks : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() == 0) return;

        String jsonString = String(value.c_str());
        Log.debug("BLE Rx: " + jsonString);

        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, jsonString);

        if (error) {
            Log.error("BLE: JSON Parse Error");
            return;
        }

        if (doc.containsKey("cmd")) {
            String cmd = doc["cmd"];
            if (cmd == "unlock") {
                if (VehicleController.unlock()) {
                    BLE.notify("{\"ok\":true}");
                } else {
                    BLE.notify("{\"ok\":false, \"msg\":\"already unlocked\"}");
                }
            } else if (cmd == "lock") {
                if (VehicleController.lock()) {
                    BLE.notify("{\"ok\":true}");
                } else {
                    BLE.notify("{\"ok\":false, \"msg\":\"already locked\"}");
                }
            } else if (cmd == "ping") {
                BLE.notify("{\"pong\":true}");
            } else {
                BLE.notify("{\"ok\":false, \"msg\":\"unknown cmd\"}");
            }
        }
    }
};

void BLEManager::begin() {
    NimBLEDevice::init("L200 Nexus ACP");

    server = NimBLEDevice::createServer();
    server->setCallbacks(new MyServerCallbacks());

    service = server->createService(SERVICE_UUID);

    commandChar = service->createCharacteristic(
        COMMAND_UUID,
        NIMBLE_PROPERTY::WRITE
    );
    commandChar->setCallbacks(new MyCommandCallbacks());

    statusChar = service->createCharacteristic(
        STATUS_UUID,
        NIMBLE_PROPERTY::NOTIFY
    );

    service->start();

    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(false);
    pAdvertising->start();

    Log.info("BLE Manager Ready");
}

void BLEManager::update() {
    // NimBLE is event-driven, no polling needed for basic ops
}

bool BLEManager::connected() const {
    return Vehicle.bleConnected;
}

void BLEManager::notify(const String& message) {
    if (statusChar) {
        statusChar->setValue(message.c_str());
        statusChar->notify();
    }
}
