#ifndef BLE_MODULE_HPP
#define BLE_MODULE_HPP

#include <ArduinoBLE.h>

namespace paddy
{

static const int MAX_JWT_CHARACTERISTIC_BUFFER_SIZE = 1000;
static const int MAX_CHARACTERISTIC_BUFFER_SIZE = 32;

class BleModule
{
private:
    // ---- Advertisement ----
    BLEService bleService;
    BLEDevice central;

    // ---- Serial (Read Only) ----
    BLEStringCharacteristic bleSerialChar;

    // ---- SSID ----
    BLEStringCharacteristic bleSsidChar;
    const char* ssidChar = "";

    // ---- Password ----
    BLEStringCharacteristic blePassChar;
    const char* passChar = "";

    // ---- Username (Enterprise) ----
    BLEStringCharacteristic bleEUsernameChar;
    const char* eUsernameChar = "";

    // ---- Password (Enterprise) ----
    BLEStringCharacteristic bleEPasswordChar;
    const char* ePasswordChar = "";

    // ---- MQTT JWT ----
    BLEStringCharacteristic bleJwtChar;

public:    
    static BleModule& getInstance();

    void startBle();
    void getCredentials();
    void stopBle();
    bool check();

    inline const char* getSsid() { return ssidChar; }
    inline const char* getPass() { return passChar; }
    inline const char* getEUsername() { return eUsernameChar; }
    inline const char* getEPassword() { return ePasswordChar; }

private:
    BleModule(
        const char* deviceSerial,
        const char* serviceUuid,
        const char* serialUuid,
        const char* ssidUuid,
        const char* passUuid,
        const char* eUsernameUuid,
        const char* ePasswordUuid,
        const char* jwtUuid
    ) : bleService(serviceUuid),
        bleSerialChar(serialUuid, BLERead, MAX_CHARACTERISTIC_BUFFER_SIZE),
        bleSsidChar(ssidUuid, BLEWrite, MAX_CHARACTERISTIC_BUFFER_SIZE),
        blePassChar(passUuid, BLEWrite, MAX_CHARACTERISTIC_BUFFER_SIZE),
        bleEUsernameChar(eUsernameUuid, BLEWrite, MAX_CHARACTERISTIC_BUFFER_SIZE),
        bleEPasswordChar(ePasswordUuid, BLEWrite, MAX_CHARACTERISTIC_BUFFER_SIZE),
        bleJwtChar(jwtUuid, BLEWrite, MAX_JWT_CHARACTERISTIC_BUFFER_SIZE) {}
    BleModule(BleModule const&);
    BleModule& operator=(BleModule const&);
};

}

#endif