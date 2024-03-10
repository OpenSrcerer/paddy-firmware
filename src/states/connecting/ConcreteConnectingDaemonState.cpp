#include "ConnectingDaemonState.hpp"
#include "../../mqtt/MqttModule.hpp"
#include "../../DaemonSecrets.hpp"


namespace paddy
{

void Connecting::enter(Daemon *daemon)
{
    MqttModule* mqttModule = &MqttModule::getInstance();

    
}

void Connecting::exit(Daemon *daemon)
{
}

void Connecting::toggle(Daemon *daemon)
{
    // daemon->setState(SomeOtherState::getInstance());
}

DaemonState &Connecting::getInstance()
{
    static Connecting singleton;
    return singleton;
}

}