#ifndef CONNECTING_DAEMON_STATE_HPP
#define CONNECTING_DAEMON_STATE_HPP

#include "../../daemon/Daemon.hpp"
#include "../DaemonState.hpp"

namespace paddy
{

class Connecting : public DaemonState
{
public:
	inline String &name() { 
        static String name("Connecting");
        return name;
    }
	
	void enter(Daemon *daemon);
	void exit(Daemon *daemon);
	void toggle(Daemon *daemon);

	static DaemonState &getInstance(Daemon* daemon);

private:
	Connecting(Daemon* daemon) {
		this->daemon = daemon;
	}
	Connecting(Connecting const&);
    Connecting& operator=(Connecting const&);
};

}

#endif