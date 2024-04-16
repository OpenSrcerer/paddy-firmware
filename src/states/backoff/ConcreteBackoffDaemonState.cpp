#include "BackoffDaemonState.hpp"
#include "../../ble/BleModule.hpp"
#include "../../mqtt/MqttModule.hpp"
#include "../../storage/StorageModule.hpp"
#include "../connecting/ConnectingDaemonState.hpp"
#include "../setup/SetupDaemonState.hpp"

namespace paddy
{

void Backoff::enter(Daemon *daemon)
{
    MqttModule* mqtt = &MqttModule::getInstance();
    
    if (mqtt->deviceWasReset())
    {
        Serial.println("[State: BACKOFF] Device was reset through MQTT.");
        StorageModule::getInstance().clearAll();
        daemon->reset(); // Next step is indirectly done when the device restarts.
        daemon->setState(Setup::getInstance()); // This statement has no effect.
    }

    Serial.println("[State: BACKOFF] Awaiting reset for 60 seconds and retrying connection otherwise.");
    daemon->toggle();
}

void Backoff::toggle(Daemon *daemon)
{
    BleModule* ble = &BleModule::getInstance();
    StorageModule* storage = &StorageModule::getInstance();

    ble->startBle();
    bool wasReset = ble->awaitReset();
    ble->stopBle();

    if (wasReset)
    {
        Serial.println("[State: BACKOFF] Device was reset through BLE.");
        StorageModule::getInstance().clearAll();
        daemon->reset(); // Next step is indirectly done when the device restarts.
        daemon->setState(Setup::getInstance()); // This statement has no effect.
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