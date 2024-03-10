#include "SetupDaemonState.hpp"
#include "../connecting/ConnectingDaemonState.hpp"
#include "../../wifi/WifiModule.hpp"
#include "../../ble/BleModule.hpp"

namespace paddy
{

void Setup::enter(Daemon *daemon)
{
    BleModule* ble = &BleModule::getInstance();
    WifiModule* wifi = &WifiModule::getInstance();

    // ------ Bluetooth Phase ------
    ble->setupBle();
    do {
        ble->startBle();
        ble->getCredentials(); // Blocks until credentials are retrieved
        ble->stopBle(); // BLE and WiFi cannot be active at the same time (at least on Nano IoT 33)
    } while (!wifi->startWifi(ble));

    daemon->toggle(); // Move to next stage
}

void Setup::exit(Daemon *daemon)
{
}

void Setup::toggle(Daemon *daemon)
{
    daemon->setState(Connecting::getInstance());
}

DaemonState &Setup::getInstance()
{
    static Setup singleton;
    return singleton;
}

}