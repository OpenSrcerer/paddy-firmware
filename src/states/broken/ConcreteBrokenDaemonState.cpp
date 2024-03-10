#include "BrokenDaemonState.hpp"

namespace paddy
{

DaemonState &Broken::getInstance()
{
    static Broken singleton;
    return singleton;
}

}