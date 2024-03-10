#ifndef MQTT_MODULE_HPP
#define MQTT_MODULE_HPP

#include <WiFiSSLClient.h>
#include <ArduinoMqttClient.h>

namespace paddy
{

class MqttModule
{
private:
    WiFiSSLClient wifiClient;
    MqttClient mqttClient;

public:
    static MqttModule &getInstance();

    void startMqtt();
    void onMqttMessage(int messageSize);
    inline void poll() { mqttClient.poll(); }

private:
    MqttModule() : mqttClient(wifiClient) {}
    MqttModule(MqttModule const&);
    MqttModule& operator=(MqttModule const&);
};

}

#endif