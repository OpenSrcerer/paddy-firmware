#ifndef MQTT_MODULE_HPP
#define MQTT_MODULE_HPP

#include <WiFiSSLClient.h>
#include <ArduinoMqttClient.h>

namespace paddy
{

class MqttModule
{
private:
    MqttClient mqttClient;

public:
    MqttModule(WiFiSSLClient &client) : mqttClient(client) {}

    static MqttModule &getInstance(WiFiSSLClient& client);

    void startMqtt();
    void onMqttMessage();
};

}

#endif