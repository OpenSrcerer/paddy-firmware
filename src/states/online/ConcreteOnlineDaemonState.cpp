#include "OnlineDaemonState.hpp"
#include "../../mqtt/MqttModule.hpp"
#include "../../wifi/WifiModule.hpp"
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
    MqttModule* mqttModule = &MqttModule::getInstance();
    WifiModule* wifiModule = &WifiModule::getInstance();

    unsigned long spins = 0;
    pingMillis = millis();
    while (true)
    {
        if (millis() - pingMillis >= PING_INTERVAL) {
            mqttModule->sendMessage("ping");
            pingMillis = millis();

            Serial.println(String("[State: ONLINE] Spins: ") + String(spins / 60) + "/s.");
            spins = 0;
        }

        if (!mqttModule->isConnected())
        {
            mqttModule->stopMqtt();
            wifiModule->stopWifi();

            daemon->setState(Backoff::getInstance());
            return;
        }

        mqttModule->poll();
        spins++;
    }
}

DaemonState &Online::getInstance()
{
    static Online singleton;
    return singleton;
}

}