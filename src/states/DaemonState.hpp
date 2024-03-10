#ifndef DAEMON_STATE_HPP
#define DAEMON_STATE_HPP

#include "../daemon/Daemon.hpp"

namespace paddy
{

class Daemon; // Resolve circular dependency

class DaemonState
{
public:
    virtual String &name() = 0;

    virtual void enter(Daemon *daemon) = 0;  // Do upon entering state
    virtual void toggle(Daemon *daemon) = 0; // Transition to some state
    virtual void exit(Daemon *daemon) = 0;   // Do upon exiting state

    virtual ~DaemonState() {}

protected:
    Daemon* daemon;
};

}

#endif