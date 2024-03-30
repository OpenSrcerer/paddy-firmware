#ifndef CONTROL_MODULE_HPP
#define CONTROL_MODULE_HPP

#include "../daemon/Daemon.hpp"

namespace paddy
{

class ControlModule
{

private:
    bool switchState;

public:
    static ControlModule &getInstance();

    void on();
    void toggle();
    void off();

    inline bool isOn() { return switchState; }

private:
    ControlModule() {}
    ControlModule(ControlModule const&);
    ControlModule& operator=(ControlModule const&);

};

}

#endif