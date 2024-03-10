#include "MqttModule.hpp"
#include "../storage/StorageModule.hpp"
#include "../DaemonGlobals.hpp"

// Topics
String WRITE_TOPIC   = "daemon/v1/writes/" + String(DEVICE_SERIAL);
String READ_TOPIC    = "daemon/v1/reads/" + String(DEVICE_SERIAL);

namespace paddy
{

void MqttModule::startMqtt()
{
    Serial.print("[MqttModule] Connecting to broker: ");
    Serial.print(BROKER_HOST);
    Serial.print(":");
    Serial.println(BROKER_PORT);

    mqttClient.setUsernamePassword("jwt-here", "");

    if (!mqttClient.connect(BROKER_HOST, BROKER_PORT)) {
        Serial.print("[MqttModule] Connection failed! Error code: ");
        Serial.println(mqttClient.connectError());

        while (1);
    }

    Serial.println("[MqttModule] Connection successful!");
    Serial.print("[MqttModule] Subscribing to: ");
    Serial.println(READ_TOPIC);

    // mqttClient.onMessage(onMqttMessage);
    int subStatus = mqttClient.subscribe(READ_TOPIC.c_str());
}

void MqttModule::onMqttMessage()
{
    // char receivedMessage[messageSize];
    // int i = 0;
    // while (mqttClient.available()) {
    //     receivedMessage[i] = (char) mqttClient.read();
    //     ++i;
    // }
    // String receivedString = String(receivedMessage);

    // Serial.print("[MqttModule] Received MQTT Message: ");
    // Serial.println(receivedString);

    // if (strncmp(receivedMessage, "toggle", 6) == 0) {
    //     lightStatus = !lightStatus;
    //     String response = String("{\"message\":\"toggled\"}");

    //     mqttClient.beginMessage(WRITE_TOPIC);
    //     mqttClient.print(response);
    //     mqttClient.endMessage();
    // }
}


MqttModule& MqttModule::getInstance()
{
    static MqttModule singleton;
    return singleton;
}

}