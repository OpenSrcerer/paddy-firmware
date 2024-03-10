#ifndef WIFI_MODULE_HPP
#define WIFI_MODULE_HPP

#include <WiFiNINA.h>
#include <WiFiSSLClient.h>

namespace paddy
{

class WifiModule
{
private:
    WiFiSSLClient client;

public:
    static WifiModule& getInstance();

    inline WiFiSSLClient& getClient() { return client; }

    bool startWifi(const char* ssid, const char* pass);
    void stopWifi();
    bool check();

private:
    WifiModule() {}
    WifiModule(WifiModule const&);
    WifiModule& operator=(WifiModule const&);
};

}

#endif