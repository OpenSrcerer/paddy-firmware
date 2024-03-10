#include "InitDaemonState.hpp"
#include "../connecting/ConnectingDaemonState.hpp"
#include "../setup/SetupDaemonState.hpp"

namespace paddy
{

void Init::enter(Daemon *daemon)
{
    Serial.println("[INIT] NOT IMPLEMENTED");
    daemon->toggle();
}

void Init::toggle(Daemon *daemon)
{
    daemon->setState(Setup::getInstance());
}

DaemonState &Init::getInstance()
{
    static Init singleton;
    return singleton;
}

}