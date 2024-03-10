#ifndef SETUP_DAEMON_STATE_HPP
#define SETUP_DAEMON_STATE_HPP

#include "../../daemon/Daemon.hpp"
#include "../DaemonState.hpp"

namespace paddy
{

class Setup : public DaemonState
{
public:
    inline String &name() { 
        static String name("Setup");
        return name;
    }

    void enter(Daemon *daemon);
    void exit(Daemon *daemon);
    void toggle(Daemon *daemon);
    
    static DaemonState &getInstance();

private:
    Setup() {}
    Setup(Setup const&);
    Setup& operator=(Setup const&);
};

}

#endif