#ifndef STORAGE_MODULE_HPP
#define STORAGE_MODULE_HPP

// #define EEPROM_EMULATION_SIZE     (4 * 1024)
#define FLASH_DEBUG 0 // 0-2

#include <FlashStorage_SAMD.h>

namespace paddy
{

class StorageModule
{

public:
    static MqttModule &getInstance(WiFiSSLClient& client);

    void startMqtt();
    void onMqttMessage();

private:
    StorageModule() {}
    StorageModule(StorageModule const&);
    StorageModule& operator=(StorageModule const&);
};

}

#endif