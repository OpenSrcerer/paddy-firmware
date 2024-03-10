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

    static DaemonState &getInstance();

private:
    Init() {}
    Init(Init const&);
    Init& operator=(Init const&);
};

}

#endif