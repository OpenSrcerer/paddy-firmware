#include "ControlModule.hpp"
#include "../DaemonGlobals.hpp"

namespace paddy
{

void ControlModule::on()
{
    if (switchState == false) 
    {
        Serial.println("[ControlModule] On!");
        switchState = true;
        digitalWrite(CONTROL_PIN, HIGH);
    }
}

void ControlModule::off()
{
    if (switchState == true) 
    {
        Serial.println("[ControlModule] Off!");
        switchState = false;
        digitalWrite(CONTROL_PIN, LOW);
    }
}

void ControlModule::toggle()
{
    Serial.println("[ControlModule] Toggle!");
    switchState = !switchState;
    digitalWrite(CONTROL_PIN, switchState);
}

ControlModule& ControlModule::getInstance()
{
    static ControlModule singleton;
    return singleton;
}

}