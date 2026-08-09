#pragma once

#include <Arduino.h>
#include <NimBLEDevice.h>

class BLEManager
{
public:

    void begin();

    void update();

    void notifyStatus();

    bool connected() const;

private:

    NimBLEServer* server = nullptr;

    NimBLEService* service = nullptr;

    NimBLECharacteristic* commandChar = nullptr;

    NimBLECharacteristic* statusChar = nullptr;

    bool clientConnected = false;
};

extern BLEManager BLE;
