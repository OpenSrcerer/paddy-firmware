#include "Daemon.hpp"
#include "../states/boot/BootDaemonState.hpp"
#include "../DaemonGlobals.hpp"


namespace paddy
{

Daemon::Daemon()
{
    currentState = &Boot::getInstance();
}

void Daemon::setState(DaemonState &newState)
{
    Serial.print(String("\n[Daemon-") + String(DEVICE_SERIAL) + "] ------ <");
    Serial.print(currentState->name());
    Serial.print(" --> ");
    Serial.print(newState.name());
    Serial.println("> ------\n");

    currentState->exit(this);
    currentState = &newState;
    currentState->enter(this);
}

void Daemon::toggle()
{
    currentState->toggle(this);
}

}