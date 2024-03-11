#include "WifiModule.hpp"
#include "../storage/StorageModule.hpp"

namespace paddy
{

void WifiModule::startWifi()
{
    StorageModule* storage = &StorageModule::getInstance();

    const char* ssid = storage->readAt(SSID_ADDRESS);
    const char* pass = storage->readAt(PASS_ADDRESS);
    const char* eUsername = storage->readAt(E_USERNAME_ADDRESS);
    const char* ePassword = storage->readAt(E_PASSWORD_ADDRESS);

    Serial.print("[WifiModule] Connection attempt:\n[WifiModule] SSID <");
    Serial.print(ssid);

    Serial.print(">\n[WifiModule] ");
    Serial.print("Password: <");
    Serial.print(pass);

    Serial.print(">\n[WifiModule] ");
    Serial.print("Enterprise Username: <");
    Serial.print(eUsername);

    Serial.print(">\n[WifiModule] ");
    Serial.print("Enterprise Password: <");
    Serial.print(ePassword);
    Serial.println(">");

    int connectTries = 1;
    int connectStatus = WL_DISCONNECTED;
    while (connectTries <= 3) {

        Serial.print("[WifiModule] Connection attempt ");
        Serial.print(connectTries);
        Serial.println("/3:");

        // Assumes there is some form of storage.
        // The job of declining the storage is to the INIT state.
        if (storage->hasEnterprise())
        {
            Serial.println("[WifiModule] Starting Enterprise Wifi...");
            connectStatus = WiFi.beginEnterprise(ssid, eUsername, ePassword);
        }
        else if (storage->hasPersonal())
        {
            Serial.println("[WifiModule] Starting Personal Wifi...");
            connectStatus = WiFi.begin(ssid, pass);
        }
        else
        {
            Serial.println("[WifiModule] Starting Insecure Wifi...");
            connectStatus = WiFi.begin(ssid);
        }

        if (connectStatus == WL_CONNECTED) {
            Serial.println("[WifiModule] Connected to wireless network!");
            connectionSucceeded = true;
            return;
        }

        ++connectTries;
    }

    Serial.println("[WifiModule] Connection failed, probably bad credentials.");
    stopWifi();
    connectionSucceeded = false;
    return;
}

void WifiModule::stopWifi()
{
    WiFi.disconnect();
    WiFi.end();
    Serial.println("[WifiModule] Connection ended.");
}

bool WifiModule::checkHardware() {
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