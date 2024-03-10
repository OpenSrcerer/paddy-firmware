#include "WifiModule.hpp"

namespace paddy
{

bool WifiModule::startWifi(BleModule* ble)
{
    Serial.print("[WifiModule] Attempting to connect with credentials:\n[WifiModule] SSID <");
    Serial.print(ble->getSsid());
    Serial.print(">\n[WifiModule] ");
    Serial.print("Password: <");
    Serial.print(ble->getPass());
    Serial.print(">\n[WifiModule] ");
    Serial.print("Enterprise Username: <");
    Serial.print(ble->getEUsername());
    Serial.print(">\n[WifiModule] ");
    Serial.print("Enterprise Password: <");
    Serial.print(ble->getEPassword());
    Serial.println(">");

    int connectTries = 1;
    int connectStatus = WL_DISCONNECTED;
    while (connectTries <= 3) {

        Serial.print("[WifiModule] Connection attempt ");
        Serial.print(connectTries);
        Serial.println("/3:");

        if (strlen(ble->getEUsername()) == 0)
        {
            Serial.println("[WifiModule] Starting Personal Wifi...");
            connectStatus = WiFi.begin(ble->getSsid(), ble->getPass());
        }
        else
        {
            Serial.println("[WifiModule] Starting Enterprise Wifi...");
            connectStatus = WiFi.beginEnterprise(ble->getSsid(), ble->getEUsername(), ble->getEPassword());
        }

        if (connectStatus == WL_CONNECTED) {
            Serial.println("[WifiModule] Connected to wireless network!");
            return true;
        }

        ++connectTries;
    }

    Serial.println("[WifiModule] Connection failed, probably bad credentials.");
    stopWifi();
    return false;
}

void WifiModule::stopWifi()
{
    WiFi.disconnect();
    WiFi.end();
    Serial.println("[WifiModule] Connection ended.");
}

bool WifiModule::check() {
    // Only used because there's a bug
    // If WiFi.status() is called without this,
    // the subsequent call will block forever.
    WiFi.begin("42"); // Fake Wifi
    if (WiFi.status() == WL_NO_MODULE)
    {
        Serial.println("[WifiModule] Unable to communicate with Wifi module, possibly hardware failure.");
        return false;
    }
    WiFi.disconnect();
    WiFi.end();
    return true;
}

WifiModule& WifiModule::getInstance()
{
    static WifiModule singleton;
    return singleton;
}

}