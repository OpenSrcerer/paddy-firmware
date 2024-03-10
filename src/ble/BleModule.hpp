#ifndef BLE_MODULE_HPP
#define BLE_MODULE_HPP

#include <ArduinoBLE.h>

namespace paddy
{

static const int MAX_CHARACTERISTIC_BUFFER_SIZE = 32;

class BleModule
{
private:
    // ---- Advertisement ----
    BLEService bleWifiService;
    BLEStringCharacteristic bleSsidChar;
    BLEStringCharacteristic blePassChar;

    // ---- Data Handling ----
    BLEDevice central;
    const char* ssidChar = "";
    const char* passChar = "";

public:    
    static BleModule& getInstance();

    void startBle();
    void getWifiCredentials();
    void stopBle();
    bool check();

    inline const char* getSsid() { return ssidChar; }
    inline const char* getPass() { return passChar; }

private:
    BleModule(
        const char* wifiUuid,
        const char* ssidUuid,
        const char* passUuid,
        int passFlags
    ) : bleWifiService(wifiUuid),
        bleSsidChar(ssidUuid, passFlags, MAX_CHARACTERISTIC_BUFFER_SIZE),
        blePassChar(passUuid, passFlags, MAX_CHARACTERISTIC_BUFFER_SIZE) {}
    BleModule(BleModule const&);
    BleModule& operator=(BleModule const&);
};

}

#endif