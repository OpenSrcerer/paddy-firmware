#include "OnlineDaemonState.hpp"
#include "../../mqtt/MqttModule.hpp"
#include "../../wifi/WifiModule.hpp"
#include "../../power/PowerModule.hpp"
#include "../backoff/BackoffDaemonState.hpp"

namespace paddy
{

void Online::enter(Daemon *daemon)
{
    (&MqttModule::getInstance())->sendMessage("ping");

    daemon->toggle();
}

void Online::toggle(Daemon *daemon)
{
    MqttModule* mqttModule   = &MqttModule::getInstance();
    WifiModule* wifiModule   = &WifiModule::getInstance();
    PowerModule* powerModule = &PowerModule::getInstance();

    unsigned long spins = 0;

    measureMillis = millis();
    pingMillis = millis();

    while (true)
    {
        mqttModule->poll();

        if (millis() - pingMillis >= PING_INTERVAL)
        {
            pingMillis = millis();

            // Get the WiFi signal strength
            String rssi = String(WiFi.RSSI());
            mqttModule->sendMessage("ping", &rssi);

            Serial.println(String("[State: ONLINE] Spins: ") + String(spins / 60) + "/s.");
            spins = 0;
        }

        if (millis() - measureMillis >= MEASURE_INTERVAL)
        {
            measureMillis = millis();
            
            String powerUsage = String(powerModule->getPowerUsageWatts(), 1); // 1 decimal place
            mqttModule->sendMessage("power", &powerUsage);
        }

        if (!mqttModule->isConnected() || mqttModule->deviceWasReset() || mqttModule->deviceWasRotated())
        {
            mqttModule->stopMqtt();
            wifiModule->stopWifi();

            daemon->setState(Backoff::getInstance());
            return;
        }

        spins++;
    }
}

DaemonState &Online::getInstance()
{
    static Online singleton;
    return singleton;
}

}