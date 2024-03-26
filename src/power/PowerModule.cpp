#include "PowerModule.hpp"

namespace paddy
{

int PowerModule::getPowerUsageWatts()
{
    int I = energyMonitor.calcIrms(CT_SAMPLES); // Calculate RMS Current
    int w = (I * CT_VOLTAGE) - CT_LINEAR_SHIFT; // Then the power (watts)

    // Wattage less than zero shouldn't happen normally, but occurs
    // due to the linear shift.
    if (w < 0)
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

