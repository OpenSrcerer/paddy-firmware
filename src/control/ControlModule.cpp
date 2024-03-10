#include "ControlModule.hpp"
#include "../DaemonGlobals.hpp"

namespace paddy
{

void ControlModule::on()
{
    switchState = true;
    digitalWrite(CONTROL_PIN, HIGH);
}

void ControlModule::off()
{
    switchState = false;
    digitalWrite(CONTROL_PIN, LOW);
}

void ControlModule::toggle()
{
    switchState = !switchState;
    digitalWrite(CONTROL_PIN, switchState);
}

ControlModule& ControlModule::getInstance()
{
    static ControlModule singleton;
    return singleton;
}

}