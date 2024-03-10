#ifndef STORAGE_MODULE_HPP
#define STORAGE_MODULE_HPP

// #define EEPROM_EMULATION_SIZE     (4 * 1024)
#define FLASH_DEBUG 0 // 0-2

#include <Arduino.h>

namespace paddy
{

class StorageModule
{

private:
    char* memoryJwt = "";

public:
    static StorageModule &getInstance();

    // May be empty
    const char* readJwt();
    void writeJwt(const char* jwt);

private:
    StorageModule() {}
    StorageModule(StorageModule const&);
    StorageModule& operator=(StorageModule const&);

    void padUntilLength(String &string, int length);
    void read(String &outStr, uint16_t startAddress, uint16_t endAddress);
    void write(const char *value, size_t length, uint16_t startAddress);

};

}

#endif