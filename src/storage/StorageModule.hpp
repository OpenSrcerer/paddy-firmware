#ifndef STORAGE_MODULE_HPP
#define STORAGE_MODULE_HPP

#define EEPROM_EMULATION_SIZE  (1024 + 512)  // (2 * 1024)
#define FLASH_DEBUG            0             // 0-2

#include <Arduino.h>

// ------------------- Storage Schema -----------------------
// The way this storage works on the EEPROM
// is by storing a data length at a known address.

// The data length is always 4 chars (done by the)
// padUntilLength function.

// The data immediately succeeds this length. Example:
// 00010helloworld
// ^             ^
// 0             13

// The known addresses for the starting length pointers are:

const uint16_t JWT_ADDRESS        = 0;    // 4 (len) + 1024 (JWT)        = 1027 MAX
const uint16_t SSID_ADDRESS       = 1028; // 4 (len) + 64   (SSID)       = 1095 MAX
const uint16_t PASS_ADDRESS       = 1096; // 4 (len) + 128  (PASS)       = 1228 MAX
const uint16_t E_USERNAME_ADDRESS = 1229; // 4 (len) + 128  (E_USERNAME) = 1361 MAX
const uint16_t E_PASSWORD_ADDRESS = 1362; // 4 (len) + 128  (E_PASSWORD) = 1494 MAX

// ---------------------------------------------------------

namespace paddy
{

class StorageModule
{

private:
    String memoryJwt;
    String memorySsid;
    String memoryPass;
    String memoryEUsername;
    String memoryEPassword;

public:
    static StorageModule &getInstance();

    bool hasInsecure();
    bool hasPersonal();
    bool hasEnterprise();

    const char* readAt(int at);

    void writeAt(const char* toWrite, int at);

    void clearAll();
    void deleteAt(int at);

    String& getMemoryItemByAddress(size_t addr);

private:
    StorageModule() {}
    StorageModule(StorageModule const&);
    StorageModule& operator=(StorageModule const&);

    bool hasAt(int at);
    bool isAddress(const char* addr);
    
    void padUntilLength(String &string, int length);
    void read(String &outStr, uint16_t startAddress, uint16_t endAddress);
    void write(const char *value, size_t length, uint16_t startAddress);

};

}

#endif