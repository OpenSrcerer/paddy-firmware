#include "BleModule.hpp"
#include "../DaemonSecrets.hpp"

// ------ Bluetooth Configuration ------
char BLE_NAME[] = SECRET_BLE_NAME;
char WIFI_UUID[] = SECRET_WIFI_UUID;
char SSID_UUID[] = SECRET_SSID_UUID;
char PASS_UUID[] = SECRET_PASS_UUID;

namespace paddy
{

void BleModule::startBle()
{
    // Set up BLE service and characteristics
    BLE.setLocalName(BLE_NAME);
    BLE.setAdvertisedService(bleWifiService);
    bleWifiService.addCharacteristic(bleSsidChar);
    bleWifiService.addCharacteristic(blePassChar);

    // Add the service and advertise it
    BLE.addService(bleWifiService);
    BLE.advertise();

    Serial.println("BLE listening...");
}

void BleModule::stopBle()
{
    central.disconnect();
    BLE.stopAdvertise();
    BLE.end();
    Serial.println("BLE ended.");
}

void BleModule::getWifiCredentials()
{
    while (1)
    {
        central = BLE.central();

        if (!central)
        {
            continue;
        }

        Serial.print("Connected to BLE Central: ");
        Serial.println(central.address());

        while (central.connected())
        {
            if (!central.connected())
            {
                Serial.println("BLE Central disconnected!");
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

            if (strlen(ssidChar) != 0 && strlen(passChar) != 0)
            {
                stopBle();

                Serial.print("SSID Retrieved: ");
                Serial.println(ssidChar);

                Serial.print("Pass Retrieved: ");
                Serial.println(passChar);

                return;
            }
        }
    }
}

bool BleModule::check() 
{
    if (!BLE.begin())
    {
        Serial.println("Starting BLE failed!");
        return false;
    }
    return true;
}

BleModule& BleModule::getInstance()
{
    static BleModule singleton(WIFI_UUID, SSID_UUID, PASS_UUID, BLEWrite);
    return singleton;
}

}