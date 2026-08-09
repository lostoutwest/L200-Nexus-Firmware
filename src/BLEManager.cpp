#include "../include/BLEManager.h"

#include "../include/VehicleController.h"
#include "../include/config.h"
#include "../include/Logger.h"

BLEManager BLE;

//======================================================
// Server Callbacks
//======================================================

class ServerCallbacks : public NimBLEServerCallbacks
{
    void onConnect(NimBLEServer* server,
                   NimBLEConnInfo& connInfo) override
    {
        Vehicle.setBLEConnected(true);

        Log.info("[BLE] Client Connected");
    }

    void onDisconnect(NimBLEServer* server,
                      NimBLEConnInfo& connInfo,
                      int reason) override
    {
        Vehicle.setBLEConnected(false);

        Log.info("[BLE] Client Disconnected");

        NimBLEDevice::getAdvertising()->start();
    }
};

//======================================================
// Command Characteristic
//======================================================

class CommandCallbacks : public NimBLECharacteristicCallbacks
{
    void onWrite(NimBLECharacteristic* characteristic,
                 NimBLEConnInfo& connInfo) override
    {
        std::string value = characteristic->getValue();

        if(value.empty())
            return;

        String cmd = String(value.c_str());

        cmd.trim();

        cmd.toUpperCase();

        Log.print("[BLE] RX : ");

        Log.info(cmd);

        //------------------------------------------------

        if(cmd == "LOCK")
        {
            Vehicle.lock();
        }
        else if(cmd == "UNLOCK")
        {
            Vehicle.unlock();
        }
        else if(cmd == "IGNITION_ON")
        {
            Vehicle.ignitionOn();
        }
        else if(cmd == "IGNITION_OFF")
        {
            Vehicle.ignitionOff();
        }
        else if(cmd == "START_ENGINE")
        {
            Vehicle.startEngine();
        }
        else if(cmd == "HEADLIGHT_ON")
        {
            Vehicle.headlights(true);
        }
        else if(cmd == "HEADLIGHT_OFF")
        {
            Vehicle.headlights(false);
        }

        BLE.notifyStatus();
    }
};

//======================================================
// BLE Startup
//======================================================

void BLEManager::begin()
{
    Log.info("[BLE] Initialising...");

    NimBLEDevice::init(DEVICE_NAME);

    NimBLEDevice::setPower(ESP_PWR_LVL_P9);

    server = NimBLEDevice::createServer();

    server->setCallbacks(new ServerCallbacks());

    //--------------------------------------------------

    service = server->createService(
        NimBLEUUID(SERVICE_UUID)
    );

    //--------------------------------------------------

    commandChar = service->createCharacteristic(
        NimBLEUUID(COMMAND_UUID),
        NIMBLE_PROPERTY::WRITE |
        NIMBLE_PROPERTY::WRITE_NR
    );

    commandChar->setCallbacks(
        new CommandCallbacks()
    );

    //--------------------------------------------------

    statusChar = service->createCharacteristic(
        NimBLEUUID(STATUS_UUID),
        NIMBLE_PROPERTY::READ |
        NIMBLE_PROPERTY::NOTIFY
    );

    statusChar->setValue(
        "{\"boot\":true}"
    );

    //--------------------------------------------------

    service->start();

    Log.info("[BLE] Service Started");

    //--------------------------------------------------

    NimBLEAdvertising* advertising =
        NimBLEDevice::getAdvertising();

    advertising->addServiceUUID(
        NimBLEUUID(SERVICE_UUID)
    );

    advertising->setName(DEVICE_NAME);

    advertising->enableScanResponse(true);

    advertising->start();

    Log.info("[BLE] Advertising Started");
}

//======================================================

void BLEManager::update()
{
    // Reserved for future connection monitoring
}

//======================================================

bool BLEManager::connected() const
{
    return Vehicle.bleConnected();
}

//======================================================

void BLEManager::notifyStatus()
{
    if(statusChar == nullptr)
        return;

    String json = Vehicle.json();

    statusChar->setValue(json.c_str());

    statusChar->notify();

    Log.print("[BLE] TX : ");

    Log.info(json);
}
