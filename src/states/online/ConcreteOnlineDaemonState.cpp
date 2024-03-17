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

    pingMillis = millis();
    while (true)
    {
        if (millis() - pingMillis >= PING_INTERVAL) {
            mqttModule->sendMessage("ping");
            pingMillis = millis();
        }

        if (!mqttModule->isConnected())
        {
            mqttModule->stopMqtt();
            wifiModule->stopWifi();

            daemon->setState(Backoff::getInstance());
            return;
        }

        mqttModule->poll();
    }
}

DaemonState &Online::getInstance()
{
    static Online singleton;
    return singleton;
}

}