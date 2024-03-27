#include "BackoffDaemonState.hpp"
#include "../../ble/BleModule.hpp"
#include "../connecting/ConnectingDaemonState.hpp"
#include "../setup/SetupDaemonState.hpp"

namespace paddy
{

void Backoff::enter(Daemon *daemon)
{
    Serial.println("[State: BACKOFF] Awaiting reset for 60 seconds and retrying connection otherwise.");
    daemon->toggle();
}

void Backoff::toggle(Daemon *daemon)
{
    BleModule* ble = &BleModule::getInstance();

    ble->startBle();
    bool wasReset = ble->awaitReset();
    ble->stopBle();

    if (wasReset)
    {
        Serial.println("[State: BACKOFF] Device was reset.");
        daemon->reset(); // Prevents next step...
        daemon->setState(Setup::getInstance());
    }
    else
    {
        Serial.println("[State: BACKOFF] Timer ran out. Retrying connection.");
        daemon->setState(Connecting::getInstance());
    }
}

DaemonState &Backoff::getInstance()
{
    static Backoff singleton;
    return singleton;
}

}