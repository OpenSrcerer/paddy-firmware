#include "WifiModule.hpp"

namespace paddy
{

bool WifiModule::startWifi(const char* ssid, const char* pass)
{
    Serial.print("[WifiModule] Attempting to connect:\n[WifiModule] SSID <");
    Serial.print(ssid);
    Serial.print(">\n[WifiModule] ");
    Serial.print("Password: <");
    Serial.print(pass);
    Serial.print(">");

    if (WiFi.begin(ssid, pass) == WL_CONNECTED)
    {
        Serial.println("[WifiModule] Connected!");
        return true;
    }
    else
    {
        Serial.println("[WifiModule] Connection failed, probably bad credentials.");
        stopWifi();
        return false;
    }
}

void WifiModule::stopWifi()
{
    WiFi.disconnect();
    WiFi.end();
    Serial.println("[WifiModule] Connection ended.");
}

bool WifiModule::check() {
    if (WiFi.status() == WL_NO_MODULE)
    {
        Serial.println("[WifiModule] Unable to communicate with Wifi module, possibly hardware failure.");
        return false;
    }
    return true;
}

WifiModule& WifiModule::getInstance()
{
    static WifiModule singleton;
    return singleton;
}

}