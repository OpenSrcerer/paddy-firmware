#ifndef BACKOFF_DAEMON_STATE_HPP
#define BACKOFF_DAEMON_STATE_HPP

#include "../../daemon/Daemon.hpp"
#include "../DaemonState.hpp"

namespace paddy
{

class Backoff : public DaemonState
{
public:
    inline String &name() { 
        static String name("Backoff");
        return name;
    }

    void enter(Daemon *daemon);
    void exit(Daemon *daemon) {}
    void toggle(Daemon *daemon);

    static DaemonState &getInstance();

private:
    Backoff() {}
    Backoff(Backoff const&);
    Backoff& operator=(Backoff const&);
};

}

#endif