#ifndef BOOT_DAEMON_STATE_HPP
#define BOOT_DAEMON_STATE_HPP

#include "../../daemon/Daemon.hpp"
#include "../DaemonState.hpp"

namespace paddy
{

class Boot : public DaemonState
{
public:
    inline String &name() { 
        static String name("Boot");
        return name;
    }

    void enter(Daemon *daemon);
    void exit(Daemon *daemon) {}
    void toggle(Daemon *daemon);

    static DaemonState &getInstance();

private:
    Boot() {}
    Boot(Boot const&);
    Boot& operator=(Boot const&);
};

}

#endif