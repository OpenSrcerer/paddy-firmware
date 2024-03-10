#include "ConnectingDaemonState.hpp"
#include "../../DaemonSecrets.hpp"


namespace paddy
{

void Connecting::enter(Daemon *daemon)
{
}

void Connecting::exit(Daemon *daemon)
{
}

void Connecting::toggle(Daemon *daemon)
{
    // daemon->setState(SomeOtherState::getInstance());
}

DaemonState &Connecting::getInstance(Daemon* daemon)
{
    static Connecting singleton(daemon);
    return singleton;
}

}