#include "BootDaemonState.hpp"
#include "../init/InitDaemonState.hpp"
#include "../broken/BrokenDaemonState.hpp"
#include "../../wifi/WifiModule.hpp"
#include "../../ble/BleModule.hpp"

namespace paddy
{

void Boot::enter(Daemon *daemon)
{
    daemon->toggle();
}

void Boot::toggle(Daemon *daemon)
{
    bool wifiStatus = WifiModule::getInstance().check();
    bool bleStatus = BleModule::getInstance().check();

    if (!wifiStatus || !bleStatus) 
    {
        daemon->setState(Broken::getInstance());
        return;
    }

    daemon->setState(Init::getInstance());
}

DaemonState &Boot::getInstance()
{
    static Boot singleton;
    return singleton;
}

}