#ifndef DAEMON_HPP
#define DAEMON_HPP

#include <Arduino.h>
#include "../states/DaemonState.hpp"

namespace paddy
{

class DaemonState;

class Daemon
{
public:
    Daemon();

    inline DaemonState *getCurrentState() const { return currentState; }
    
    void toggle();
    void setState(DaemonState &newState);

private:
    DaemonState *currentState;
};

}

#endif