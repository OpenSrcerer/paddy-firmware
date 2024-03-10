#include "ConnectingDaemonState.hpp"
#include "../../mqtt/MqttModule.hpp"
#include "../online/OnlineDaemonState.hpp"

namespace paddy
{

void Connecting::enter(Daemon *daemon)
{
    MqttModule* mqttModule = &MqttModule::getInstance();
    mqttModule->startMqtt();
    daemon->toggle();
}

void Connecting::exit(Daemon *daemon)
{
}

void Connecting::toggle(Daemon *daemon)
{
    daemon->setState(Online::getInstance());
}

DaemonState &Connecting::getInstance()
{
    static Connecting singleton;
    return singleton;
}

}