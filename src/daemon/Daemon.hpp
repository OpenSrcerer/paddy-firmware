#ifndef DAEMON_HPP
#define DAEMON_HPP

#include <Arduino.h>
#include "../states/DaemonState.hpp"
#include "../states/connecting/ConnectingDaemonState.hpp"
#include "../states/setup/SetupDaemonState.hpp"

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

    // This is an anti-pattern.
    // I have spent countless hours trying to understand
    // why the ArduinoBLE library fails to properly re-initialize
    // BLE Services after reset cycles, but basically what happens
    // is that after the service is shut down and restarted,
    // there are countless errors - like a missing service, or
    // missing characteristics, and it's really hard to track
    // down cause it seems to happen at random, or factors
    // outside of my control at the moment.
    
    // Thus, I am opting for the "wrong" approach to reset
    // my arduino during the reset flow. Seems fitting, does it not?
    // Well, bite me. At least I tried to fix it.
    // I have other things to focus on right now.
    inline void reset() { NVIC_SystemReset(); }

private:
    DaemonState *currentState;
};

}

#endif