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
    BLEDevice central;

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

    inline void newCharacteristics()
    {
        bleService =        new BLEService(SERVICE_UUID);
        bleSerialChar =     new BLEStringCharacteristic(SERIAL_UUID, BLERead, MAX_CHARACTERISTIC_BUFFER_SIZE);
        bleSsidChar =       new BLEStringCharacteristic(SSID_UUID, BLEWrite, MAX_CHARACTERISTIC_BUFFER_SIZE);
        blePassChar =       new BLEStringCharacteristic(PASS_UUID, BLEWrite, MAX_CHARACTERISTIC_BUFFER_SIZE);
        bleEUsernameChar =  new BLEStringCharacteristic(E_USERNAME_UUID, BLEWrite, MAX_CHARACTERISTIC_BUFFER_SIZE);
        bleEPasswordChar =  new BLEStringCharacteristic(E_PASSWORD_UUID, BLEWrite, MAX_CHARACTERISTIC_BUFFER_SIZE);
        bleJwtChar =        new BLEStringCharacteristic(JWT_UUID, BLEWrite, MAX_JWT_CHARACTERISTIC_BUFFER_SIZE);
        bleResetChar =      new BLEStringCharacteristic(RESET_UUID, BLEWrite, MAX_RESET_CHARACTERISTIC_BUFFER_SIZE);
    }

    inline void freeCharacteristics()
    {
        free(bleService);
        free(bleSerialChar);
        free(bleSsidChar);
        free(blePassChar);
        free(bleEUsernameChar);
        free(bleEPasswordChar);
        free(bleJwtChar);
        free(bleResetChar);
    }

    void startBle();
    void getCredentials();
    void stopBle();
    
    bool awaitReset();
    bool checkHardware();

private:
    BleModule() {}
    BleModule(BleModule const&);
    BleModule& operator=(BleModule const&);
};

}

#endif