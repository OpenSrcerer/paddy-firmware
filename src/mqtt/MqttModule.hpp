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
    bool deviceReset; // Only "true" if device reads "reset" topic
    bool deviceRotated; // Only "true" if device reads "reload" topic
    WiFiSSLClient wifiClient;
    MqttClient mqttClient;

public:
    static MqttModule &getInstance();

    void startMqtt();
    void stopMqtt();
    void sendMessage(const char* action, const String* message = nullptr);
    void onMqttMessage(int messageSize);

    inline void poll() { mqttClient.poll(); }
    inline bool isSucceeded() { return connectionSucceeded; }
    inline bool isConnected() { return mqttClient.connected(); }
    inline bool deviceWasReset() { return deviceReset; }
    inline bool deviceWasRotated() { return deviceRotated; }

private:
    MqttModule() : mqttClient(wifiClient) {}
    MqttModule(MqttModule const&);
    MqttModule& operator=(MqttModule const&);
};

}

#endif