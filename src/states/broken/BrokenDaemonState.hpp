#ifndef BROKEN_DAEMON_STATE_HPP
#define BROKEN_DAEMON_STATE_HPP

#include "../../daemon/Daemon.hpp"
#include "../DaemonState.hpp"

namespace paddy
{

class Broken : public DaemonState
{
public:
    inline String &name() { 
        static String name("Broken");
        return name;
    }

    void enter(Daemon *daemon) {}
    void exit(Daemon *daemon) {}
    void toggle(Daemon *daemon) {}

    static DaemonState &getInstance();

private:
    Broken() {}
};

}

#endif