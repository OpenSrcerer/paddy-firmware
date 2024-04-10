#include "PowerModule.hpp"
#include "../control/ControlModule.hpp"

namespace paddy
{

double PowerModule::getPowerUsageWatts()
{
    double I = energyMonitor.calcIrms(CT_SAMPLES); // Calculate RMS Current
    double w = (I * CT_VOLTAGE) - CT_LINEAR_SHIFT; // Then the power (watts)

    // Wattage less than zero shouldn't happen normally,
    // but can rarely occur due to the linear shift.
    // Wattages less than 5 can be measurement errors, hence discarded.
    if ((&ControlModule::getInstance())->isOn() && w < 5 || w < 15)
    {
        w = 0;
    }

    return w;
}

PowerModule& PowerModule::getInstance()
{
    static PowerModule singleton;
    return singleton;
}

}

