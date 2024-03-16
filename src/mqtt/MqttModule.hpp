#ifndef MQTT_MODULE_HPP
#define MQTT_MODULE_HPP

#include <WiFiSSLClient.h>
#include <ArduinoMqttClient.h>

namespace paddy
{

class MqttModule
{
private:
    bool connectionSucceeded; // Only updated after startWifi()
    WiFiSSLClient wifiClient;
    MqttClient mqttClient;

public:
    static MqttModule &getInstance();

    void startMqtt();
    void onMqttMessage(int messageSize);
    inline void poll() { mqttClient.poll(); }
    inline bool isSucceeded() { return connectionSucceeded; }

private:
    MqttModule() : mqttClient(wifiClient) {}
    MqttModule(MqttModule const&);
    MqttModule& operator=(MqttModule const&);
};

}

#endif