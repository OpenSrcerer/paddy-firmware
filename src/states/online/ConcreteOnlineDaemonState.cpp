#include "OnlineDaemonState.hpp"
#include "../../mqtt/MqttModule.hpp"

namespace paddy
{

void Online::enter(Daemon *daemon)
{
    MqttModule* mqttModule = &MqttModule::getInstance();

    while (true)
    {
        mqttModule->poll();
    }
}

void Online::toggle(Daemon *daemon)
{
}

DaemonState &Online::getInstance()
{
    static Online singleton;
    return singleton;
}

}