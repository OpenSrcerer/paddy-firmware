#include "BleModule.hpp"
#include "../storage/StorageModule.hpp"
#include "../DaemonGlobals.hpp"

// ------ Bluetooth Configuration ------

namespace paddy
{


void BleModule::setupBle()
{
    // Set up BLE service
    BLE.setLocalName(BLE_NAME);
    BLE.setAdvertisedService(bleService);

    // Add characteristics
    bleService.addCharacteristic(bleSerialChar);
    bleService.addCharacteristic(bleSsidChar);
    bleService.addCharacteristic(blePassChar);
    bleService.addCharacteristic(bleEUsernameChar);
    bleService.addCharacteristic(bleEPasswordChar);
    bleService.addCharacteristic(bleJwtChar);

    // Write the serial to the characteristic to be readable
    bleSerialChar.writeValue(String(DEVICE_SERIAL));

    // Add the service and advertise it
    BLE.addService(bleService);
}

void BleModule::startBle()
{
    Serial.println("[BleModule] BLE starting up...");

    BLE.advertise();

    Serial.println("[BleModule] BLE listening...");
}

void BleModule::stopBle()
{
    freeCredentials();

    central.disconnect();
    BLE.stopAdvertise();
    BLE.end();
    
    Serial.println("[BleModule] BLE ended.");
}

void BleModule::getCredentials()
{
    String jwt;

    while (1)
    {
        central = BLE.central();

        if (!central)
        {
            continue;
        }

        Serial.print("[BleModule] Connected to BLE Central: ");
        Serial.println(central.address());

        while (central.connected())
        {
            if (!central.connected())
            {
                Serial.println("[BleModule] Central disconnected!");
                BLE.advertise(); // Re-advertise after disconnection
            }

            if (bleSsidChar.written())
            {
                ssidChar = strndup(bleSsidChar.value().c_str(), bleSsidChar.value().length());
            }

            if (blePassChar.written())
            {
                passChar = strndup(blePassChar.value().c_str(), blePassChar.value().length());
            }

            if (bleEUsernameChar.written())
            {
                eUsernameChar = strndup(bleEUsernameChar.value().c_str(), bleEUsernameChar.value().length());
            }

            if (bleEPasswordChar.written())
            {
                ePasswordChar = strndup(bleEPasswordChar.value().c_str(), bleEPasswordChar.value().length());
            }

            if (bleJwtChar.written())
            {
                // Need to buffer JWT because the max write for BLE is 512 bytes
                String partialJwt = bleJwtChar.value();
                Serial.println(
                    String("[BleModule] Received partial JWT: (") + 
                    String(partialJwt.length()) + 
                    String(" chars): <") +
                    String(partialJwt) +
                    ">"
                );

                jwt = jwt + partialJwt;
                bleJwtChar.setValue("");
            }

            // Proceeds when you setup the SSID
            if (strlen(ssidChar))
            {
                // Flush JWT
                StorageModule::getInstance().writeJwt(jwt.c_str());
                return;
            }
        }
    }
}

bool BleModule::check() 
{
    if (!BLE.begin())
    {
        Serial.println("[BleModule] Starting BLE failed!");
        return false;
    }
    return true;
}

BleModule& BleModule::getInstance()
{
    static BleModule singleton(
        DEVICE_SERIAL,
        SERVICE_UUID,
        SERIAL_UUID,
        SSID_UUID,
        PASS_UUID,
        E_USERNAME_UUID,
        E_PASSWORD_UUID,
        JWT_UUID
    );
    return singleton;
}

}