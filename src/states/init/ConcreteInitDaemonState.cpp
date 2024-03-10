#include "InitDaemonState.hpp"
#include "../connecting/ConnectingDaemonState.hpp"

namespace paddy
{

void Init::enter(Daemon *daemon)
{

}

void Init::toggle(Daemon *daemon)
{
    // daemon->setState(Init::getInstance(daemon));
}

DaemonState &Init::getInstance(Daemon* daemon)
{
    static Init singleton(daemon);
    return singleton;
}

}