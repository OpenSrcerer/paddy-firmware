#include "ConnectingDaemonState.hpp"
#include "../../mqtt/MqttModule.hpp"
#include "../../wifi/WifiModule.hpp"
#include "../online/OnlineDaemonState.hpp"
#include "../backoff/BackoffDaemonState.hpp"

namespace paddy
{

void Connecting::enter(Daemon *daemon)
{
    MqttModule* mqtt = &MqttModule::getInstance();
    WifiModule* wifi = &WifiModule::getInstance();

    wifi->startWifi();
    if (wifi->isSucceeded()) {
        mqtt->startMqtt();
    }

    daemon->toggle();
}

void Connecting::toggle(Daemon *daemon)
{
    bool wifiSuccess = WifiModule::getInstance().isSucceeded();
    bool mqttSuccess = MqttModule::getInstance().isSucceeded();

    Serial.println(String("[State: CONNECTING] Wifi: " + String(wifiSuccess) + String(", MQTT: ") + String(mqttSuccess)));
    if (wifiSuccess && mqttSuccess) {
        daemon->setState(Online::getInstance());
    } else {
        // Go to backoff if cannot connect to Wifi
        // or broker for a grace period
        daemon->setState(Backoff::getInstance());
    }
}

DaemonState &Connecting::getInstance()
{
    static Connecting singleton;
    return singleton;
}

}