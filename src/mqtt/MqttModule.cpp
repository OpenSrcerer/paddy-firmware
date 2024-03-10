#include "MqttModule.hpp"
#include "../DaemonSecrets.hpp"

// ------ MQTT Configuration ------
// Authorization
char JWT[]           = SECRET_JWT;

// Broker
char BROKER_HOST[]   = SECRET_BROKER_HOST;
int  BROKER_PORT     = SECRET_BROKER_PORT;

// Topics
char DEVICE_SERIAL[] = SECRET_DEVICE_SERIAL;
char WRITE_TOPIC[]   = SECRET_WRITE_TOPIC;
char READ_TOPIC[]    = SECRET_READ_TOPIC;

namespace paddy
{

void MqttModule::startMqtt()
{
    // Serial.print("Attempting to connect to the MQTT broker: ");
    // Serial.print(BROKER_HOST);
    // Serial.print(":");
    // Serial.println(BROKER_PORT);

    // mqttClient.setUsernamePassword(JWT, "");

    // if (!mqttClient.connect(BROKER_HOST, BROKER_PORT)) {
    //     Serial.print("MQTT connection failed! Error code = ");
    //     Serial.println(mqttClient.connectError());

    //     while (1);
    // }

    // Serial.println("You're connected to the MQTT broker!");
    // Serial.print("Subscribing to: ");
    // Serial.println(READ_TOPIC);

    // mqttClient.onMessage(onMqttMessage);
    // mqttClient.subscribe(READ_TOPIC);
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

    // Serial.print("Received MQTT Message: ");
    // Serial.println(receivedString);

    // if (strncmp(receivedMessage, "toggle", 6) == 0) {
    //     lightStatus = !lightStatus;
    //     String response = String("{\"message\":\"toggled\"}");

    //     mqttClient.beginMessage(WRITE_TOPIC);
    //     mqttClient.print(response);
    //     mqttClient.endMessage();
    // }
}


MqttModule& MqttModule::getInstance(WiFiSSLClient& client)
{
    static MqttModule singleton(client);
    return singleton;
}

}