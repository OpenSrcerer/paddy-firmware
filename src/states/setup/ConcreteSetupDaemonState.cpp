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
    do {
        ble->startBle();
        ble->getWifiCredentials();
    } while (!wifi->startWifi(ble->getSsid(), ble->getPass()));

    
}

void Setup::exit(Daemon *daemon)
{

}

void Setup::toggle(Daemon *daemon)
{
    daemon->setState(Connecting::getInstance(daemon));
}

DaemonState &Setup::getInstance(Daemon* daemon)
{
    static Setup singleton(daemon);
    return singleton;
}

}