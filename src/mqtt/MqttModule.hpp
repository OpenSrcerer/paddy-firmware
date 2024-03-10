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
    static MqttModule &getInstance(WiFiSSLClient& client);

    void startMqtt();
    void onMqttMessage();

private:
    MqttModule(WiFiSSLClient &client) : mqttClient(client) {}
    MqttModule(MqttModule const&);
    MqttModule& operator=(MqttModule const&);
};

}

#endif