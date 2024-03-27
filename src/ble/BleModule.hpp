#ifndef BLE_MODULE_HPP
#define BLE_MODULE_HPP

#include <ArduinoBLE.h>
#include "../DaemonGlobals.hpp"

namespace paddy
{

static const int MAX_JWT_CHARACTERISTIC_BUFFER_SIZE = 512;
static const int MAX_CHARACTERISTIC_BUFFER_SIZE = 64;
static const int MAX_RESET_CHARACTERISTIC_BUFFER_SIZE = 1;

class BleModule
{
private:
    // ---- Advertisement ----
    BLEService* bleService;

    // ---- Serial (Read Only) ----
    BLEStringCharacteristic* bleSerialChar;

    // ---- SSID ----
    BLEStringCharacteristic* bleSsidChar;

    // ---- Password ----
    BLEStringCharacteristic* blePassChar;

    // ---- Username (Enterprise) ----
    BLEStringCharacteristic* bleEUsernameChar;

    // ---- Password (Enterprise) ----
    BLEStringCharacteristic* bleEPasswordChar;

    // ---- MQTT JWT ----
    BLEStringCharacteristic* bleJwtChar;

    // ---- Reset ----
    BLEStringCharacteristic* bleResetChar;

public:    
    static BleModule& getInstance();

    void startBle();
    void getCredentials();
    void stopBle();
    
    bool awaitReset();
    bool checkHardware();

private:
    BleModule() {}
    BleModule(BleModule const&);
    BleModule& operator=(BleModule const&);

    void setupBle();
    void newCharacteristics();
    void freeCharacteristics();
};

}

#endif