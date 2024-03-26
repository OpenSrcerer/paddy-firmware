#include "InitDaemonState.hpp"
#include "../../storage/StorageModule.hpp"
#include "../setup/SetupDaemonState.hpp"
#include "../connecting/ConnectingDaemonState.hpp"
#include "../../power/PowerModule.hpp"

namespace paddy
{

void Init::enter(Daemon *daemon)
{
    daemon->toggle();
}

void Init::toggle(Daemon *daemon)
{
    StorageModule* storageModule = &StorageModule::getInstance();
    PowerModule* powerModule = &PowerModule::getInstance();

    // Prepare the measurement module by reading a few times for calibration
    Serial.println("[State: INIT] Calibrating power measurement system...");
    for (int i = 0; i < 5; ++i)
    {
        powerModule->getPowerUsageWatts();
    }

    if (storageModule->hasInsecure() || 
        storageModule->hasPersonal() || 
        storageModule->hasEnterprise()) 
    { // Immediately connect to broker
        Serial.println("[State: INIT] Credentials found, directly connecting to broker.");
        daemon->setState(Connecting::getInstance());
    }
    else
    { // Daemon isn't configured, take user through setup flow
        Serial.println("[State: INIT] Credentials NOT found, initializing setup flow.");
        daemon->setState(Setup::getInstance());
    }
}

DaemonState &Init::getInstance()
{
    static Init singleton;
    return singleton;
}

}