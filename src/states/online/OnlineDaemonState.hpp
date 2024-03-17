#ifndef ONLINE_DAEMON_STATE_HPP
#define ONLINE_DAEMON_STATE_HPP

#include "../../daemon/Daemon.hpp"
#include "../DaemonState.hpp"
#include "../../DaemonGlobals.hpp"

namespace paddy
{

class Online : public DaemonState
{
public:
    inline String &name() { 
        static String name("Online");
        return name;
    }

    void enter(Daemon *daemon);
    void exit(Daemon *daemon) {}
    void toggle(Daemon *daemon);

    static DaemonState &getInstance();

private:
    unsigned long pingMillis;

    Online() {}
    Online(Online const&);
    Online& operator=(Online const&);
};

}

#endif