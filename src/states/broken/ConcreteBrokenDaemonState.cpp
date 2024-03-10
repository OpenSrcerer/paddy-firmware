#include "BrokenDaemonState.hpp"

namespace paddy
{

void Broken::enter(Daemon* daemon)
{
    // This is supposed to indicate to the user that
    // something is wrong with the hardware.
    while(true) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
    }
}

DaemonState &Broken::getInstance()
{
    static Broken singleton;
    return singleton;
}

}