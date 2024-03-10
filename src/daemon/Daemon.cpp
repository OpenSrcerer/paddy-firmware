#include "Daemon.hpp"
#include "../states/boot/BootDaemonState.hpp"

namespace paddy
{

Daemon::Daemon()
{
    currentState = &Boot::getInstance();
}

void Daemon::setState(DaemonState &newState)
{
    Serial.print("[STATE] <");
    Serial.print(currentState->name());
    Serial.print(" --> ");
    Serial.print(newState.name());
    Serial.println(">");

    currentState->exit(this);
    currentState = &newState;
    currentState->enter(this);
}

void Daemon::toggle()
{
    currentState->toggle(this);
}

}