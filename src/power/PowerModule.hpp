#ifndef POWER_MODULE_HPP
#define POWER_MODULE_HPP

#include <EmonLib.h>
#include "../DaemonGlobals.hpp"

namespace paddy
{

class PowerModule
{
private:
    EnergyMonitor energyMonitor;

public:
    double getPowerUsageWatts(); // Returns the measured power in Watts

    static PowerModule &getInstance();

private:
    PowerModule()
    {
        energyMonitor.current(MEASUREMENT_PIN, CT_CALIBRATE);
    }

    PowerModule(PowerModule const&);
    PowerModule& operator=(PowerModule const&);
};

}

#endif