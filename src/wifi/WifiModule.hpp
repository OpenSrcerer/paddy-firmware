#ifndef WIFI_MODULE_HPP
#define WIFI_MODULE_HPP

#include <WiFiNINA.h>
#include <WiFiSSLClient.h>

namespace paddy
{

class WifiModule
{
private:
    bool connectionSucceeded; // Only updated after startWifi()
    WiFiSSLClient client;

public:
    static WifiModule& getInstance();

    inline WiFiSSLClient& getClient() { return client; }
    inline bool isSucceeded() { return connectionSucceeded; }

    void startWifi();
    void stopWifi();

    bool checkHardware();

private:
    WifiModule() {}
    WifiModule(WifiModule const&);
    WifiModule& operator=(WifiModule const&);
};

}

#endif