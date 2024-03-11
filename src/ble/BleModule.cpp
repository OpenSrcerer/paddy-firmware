#include "BleModule.hpp"
#include "../storage/StorageModule.hpp"
#include "../DaemonGlobals.hpp"

// ------ Bluetooth Configuration ------

namespace paddy
{

void BleModule::startBle()
{
    Serial.println("[BleModule] Setting up...");

    newCharacteristics(); // Load memory

    BLE.begin();

    // Set up BLE service
    BLE.setLocalName(BLE_NAME);
    BLE.setAdvertisedService(*bleService);

    // Add characteristics
    bleService->addCharacteristic(*bleSerialChar);
    bleService->addCharacteristic(*bleSsidChar);
    bleService->addCharacteristic(*blePassChar);
    bleService->addCharacteristic(*bleEUsernameChar);
    bleService->addCharacteristic(*bleEPasswordChar);
    bleService->addCharacteristic(*bleJwtChar);
    bleService->addCharacteristic(*bleResetChar);

    // Write the serial to the characteristic to be readable
    bleSerialChar->writeValue(String(DEVICE_SERIAL));

    // Add the service
    BLE.addService(*bleService);

    Serial.println("[BleModule] Starting up...");

    BLE.advertise();

    Serial.println("[BleModule] Listening...");
}

void BleModule::stopBle()
{
    central.disconnect();
    BLE.stopAdvertise();

    // Clear characteristics
    bleService->clear();

    BLE.end();

    freeCharacteristics(); // Free memory
    
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
        central = BLE.central();
        if (!central) { continue; }

        Serial.print("[BleModule] Connected to BLE Central: ");
        Serial.println(central.address());

        while (central.connected())
        {
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
}

bool BleModule::awaitReset()
{
    StorageModule* storage = &StorageModule::getInstance();
    long startClock = millis(); // Sample time

    // Spin for 60 seconds
    while (millis() - startClock < 60000)
    {
        central = BLE.central();
        if (!central) { continue; }

        Serial.print("[BleModule] Connected to BLE Central for RESET: ");
        Serial.println(central.address());

        // If someone is connected, await them...
        while (central.connected())
        {
            startClock = millis(); // Reset timer if they disconnect

            if (bleResetChar->written())
            {
                StorageModule::getInstance().clearAll();
                return true;
            }
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

BleModule& BleModule::getInstance()
{
    static BleModule singleton;
    return singleton;
}

}