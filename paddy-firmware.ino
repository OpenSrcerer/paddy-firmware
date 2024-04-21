#include "src/daemon/Daemon.hpp"
#include "src/DaemonGlobals.hpp"

paddy::Daemon daemon;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(CONTROL_PIN, OUTPUT);

    Serial.begin(9600);

    daemon.toggle(); // Move to the first state
}

void loop()
{
    // Nothing to see here :)
}