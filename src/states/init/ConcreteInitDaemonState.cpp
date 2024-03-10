#include "InitDaemonState.hpp"
#include "../../storage/StorageModule.hpp"
#include "../setup/SetupDaemonState.hpp"
#include "../connecting/ConnectingDaemonState.hpp"

namespace paddy
{

void Init::enter(Daemon *daemon)
{
    daemon->toggle();
}

void Init::toggle(Daemon *daemon)
{
    StorageModule* storageModule = &StorageModule::getInstance();

    if (storageModule->hasJwt())
    { // Immediately connect to broker
        Serial.println("[State: INIT] JWT found, directly connecting to broker.");
        daemon->setState(Connecting::getInstance());
    }
    else
    { // Daemon isn't configured, take user through setup flow
        Serial.println("[State: INIT] JWT not found, initializing setup flow.");
        daemon->setState(Setup::getInstance());
    }
}

DaemonState &Init::getInstance()
{
    static Init singleton;
    return singleton;
}

}