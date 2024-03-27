#include "BleModule.hpp"
#include "../storage/StorageModule.hpp"
#include "../DaemonGlobals.hpp"

// ------ Bluetooth Configuration ------

namespace paddy
{

void BleModule::startBle()
{
    Serial.println("[BleModule] Prepping...");

    setupBle();

    BLE.begin();
    BLE.setLocalName(BLE_NAME);
    BLE.setDeviceName(BLE_NAME);
    BLE.setAdvertisedServiceUuid(bleService->uuid());

    Serial.println("[BleModule] Starting up...");
    
    BLE.addService(*bleService);
    BLE.advertise();

    Serial.println("[BleModule] Listening...");
}

void BleModule::stopBle()
{
    BLE.central().disconnect();
    BLE.stopAdvertise();
    BLE.end();

    freeCharacteristics();
    
    Serial.println("[BleModule] BLE ended.");
}

void BleModule::getCredentials()
{
    StorageModule* storage = &StorageModule::getInstance();

    String jwt;
    String ssid;
    String pass;
    String eUsername;
    String ePassword;

    while (true)
    {
        BLE.poll();

        if (bleSsidChar->written())
        {
            ssid = String(bleSsidChar->value());
        }

        if (blePassChar->written())
        {
            pass = String(blePassChar->value());
        }

        if (bleEUsernameChar->written())
        {
            eUsername = String(bleEUsernameChar->value());
        }

        if (bleEPasswordChar->written())
        {
            ePassword = String(bleEPasswordChar->value());
        }

        if (bleJwtChar->written())
        {
            // Need to buffer JWT because the max write for BLE is 512 bytes
            String partialJwt = bleJwtChar->value();
            Serial.println(
                String("[BleModule] Received partial JWT: (") + 
                String(partialJwt.length()) + 
                String(" chars): <") +
                String(partialJwt) +
                ">"
            );

            jwt = jwt + partialJwt;
            bleJwtChar->setValue("");
        }

        // Proceeds when you setup the SSID
        if (ssid.length())
        {
            // Write credentials to storage
            storage->writeAt(jwt.c_str(), JWT_ADDRESS);
            storage->writeAt(ssid.c_str(), SSID_ADDRESS);
            storage->writeAt(pass.c_str(), PASS_ADDRESS);
            storage->writeAt(eUsername.c_str(), E_USERNAME_ADDRESS);
            storage->writeAt(ePassword.c_str(), E_PASSWORD_ADDRESS);

            return;
        }
    }
}

bool BleModule::awaitReset()
{
    StorageModule* storage = &StorageModule::getInstance();
    long startClock = millis(); // Sample time

    // Spin for 60 seconds
    while (millis() - startClock < 60000)
    {
        BLE.poll();

        if (bleResetChar->written())
        {
            StorageModule::getInstance().clearAll();
            return true;
        }
    }
    return false;
}

bool BleModule::checkHardware() 
{
    int isAvailable = BLE.begin();
    BLE.end();
    return isAvailable;
}

void BleModule::setupBle()
{
    Serial.println("[BleModule] Setting up...");

    newCharacteristics(); // Load memory

    // Add characteristics
    bleService->addCharacteristic(*bleSerialChar);
    bleService->addCharacteristic(*bleSsidChar);
    bleService->addCharacteristic(*blePassChar);
    bleService->addCharacteristic(*bleEUsernameChar);
    bleService->addCharacteristic(*bleEPasswordChar);
    bleService->addCharacteristic(*bleJwtChar);
    bleService->addCharacteristic(*bleResetChar);

    // Write the serial to the characteristic to be readable
    bleSerialChar->setValue(String(DEVICE_SERIAL));
}

void BleModule::newCharacteristics()
{
    bleService =        new BLEService(SERVICE_UUID);

    bleSerialChar =     new BLEStringCharacteristic(SERIAL_UUID, BLERead, MAX_CHARACTERISTIC_BUFFER_SIZE);
    bleSsidChar =       new BLEStringCharacteristic(SSID_UUID, BLEWrite, MAX_CHARACTERISTIC_BUFFER_SIZE);
    blePassChar =       new BLEStringCharacteristic(PASS_UUID, BLEWrite, MAX_CHARACTERISTIC_BUFFER_SIZE);
    bleEUsernameChar =  new BLEStringCharacteristic(E_USERNAME_UUID, BLEWrite, MAX_CHARACTERISTIC_BUFFER_SIZE);
    bleEPasswordChar =  new BLEStringCharacteristic(E_PASSWORD_UUID, BLEWrite, MAX_CHARACTERISTIC_BUFFER_SIZE);
    bleJwtChar =        new BLEStringCharacteristic(JWT_UUID, BLEWrite, MAX_JWT_CHARACTERISTIC_BUFFER_SIZE);
    bleResetChar =      new BLEStringCharacteristic(RESET_UUID, BLEWrite, MAX_RESET_CHARACTERISTIC_BUFFER_SIZE);
}

void BleModule::freeCharacteristics()
{
    // Remove all characteristics first.
    bleService->clear();

    // Then delete their memory.
    delete bleSerialChar;
    delete bleSsidChar;
    delete blePassChar;
    delete bleEUsernameChar;
    delete bleEPasswordChar;
    delete bleJwtChar;
    delete bleResetChar;

    // Then the service itself.
    delete bleService;
}

BleModule& BleModule::getInstance()
{
    static BleModule singleton;
    return singleton;
}

}