#include "OnlineDaemonState.hpp"
#include "../../mqtt/MqttModule.hpp"

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

    while (true)
    {
        mqttModule->poll();
    }
}

DaemonState &Online::getInstance()
{
    static Online singleton;
    return singleton;
}

}