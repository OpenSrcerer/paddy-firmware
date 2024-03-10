#include "BleModule.hpp"
#include "../DaemonSecrets.hpp"
#include "../storage/StorageModule.hpp"

// ------ Bluetooth Configuration ------
char DEVICE_SERIAL[]    = SECRET_DEVICE_SERIAL;
char BLE_NAME[]         = SECRET_BLE_NAME;

char SERVICE_UUID[]     = SECRET_SERVICE_UUID;
char SERIAL_UUID[]      = SECRET_SERIAL_UUID;
char SSID_UUID[]        = SECRET_SSID_UUID;
char PASS_UUID[]        = SECRET_PASS_UUID;
char E_USERNAME_UUID[]  = SECRET_E_USERNAME_UUID;
char E_PASSWORD_UUID[]  = SECRET_E_PASSWORD_UUID;
char JWT_UUID[]         = SECRET_JWT_UUID;

namespace paddy
{

void BleModule::startBle()
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
    BLE.advertise();

    Serial.println("[BleModule] BLE listening...");
}

void BleModule::stopBle()
{
    central.disconnect();
    BLE.stopAdvertise();
    BLE.end();
    Serial.println("[BleModule] BLE ended.");
}

void BleModule::getCredentials()
{
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
                ssidChar = strdup(bleSsidChar.value().c_str());
            }

            if (blePassChar.written())
            {
                passChar = strdup(blePassChar.value().c_str());
            }

            if (bleEUsernameChar.written())
            {
                eUsernameChar = strdup(bleEUsernameChar.value().c_str());
            }

            if (bleEPasswordChar.written())
            {
                ePasswordChar = strdup(bleEPasswordChar.value().c_str());
            }

            if (bleJwtChar.written())
            {
                StorageModule::getInstance().writeJwt(strdup(bleJwtChar.value().c_str()));
            }

            // Proceeds when you setup the SSID
            if (strlen(ssidChar))
            {
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