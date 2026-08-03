#pragma once

#include <Arduino.h>
#include <NimBLEDevice.h>

class BLEManager
{
public:

    void begin();

    void update();

    bool connected() const;

    void notify(const String& message);

private:

    NimBLEServer* server = nullptr;

    NimBLEService* service = nullptr;

    NimBLECharacteristic* commandChar = nullptr;

    NimBLECharacteristic* statusChar = nullptr;
    NimBLECharacteristic* diagChar = nullptr;
    NimBLECharacteristic* otaChar = nullptr;
    NimBLECharacteristic* configChar = nullptr;
    NimBLECharacteristic* rgbChar = nullptr;
    NimBLECharacteristic* sensorChar = nullptr;

    bool clientConnected = false;
};

extern BLEManager BLE;
