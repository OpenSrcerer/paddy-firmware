#ifndef INIT_DAEMON_STATE_HPP
#define INIT_DAEMON_STATE_HPP

#include "../../daemon/Daemon.hpp"
#include "../DaemonState.hpp"

namespace paddy
{

class Init : public DaemonState
{
public:
    inline String &name() { 
        static String name("Init");
        return name;
    }

    void enter(Daemon *daemon);
    void exit(Daemon *daemon) {}
    void toggle(Daemon *daemon);

    static DaemonState &getInstance(Daemon* daemon);

private:
    Init(Daemon* daemon) {
        this->daemon = daemon;
    }
};

}

#endif