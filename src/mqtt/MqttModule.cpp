#include "MqttModule.hpp"
#include "../control/ControlModule.hpp"
#include "../storage/StorageModule.hpp"
#include "../DaemonGlobals.hpp"

// Topics
String WRITES   = WRITE_TOPIC + String(DEVICE_SERIAL);
String READS    = READ_TOPIC + String(DEVICE_SERIAL);

namespace paddy
{

void MqttModule::startMqtt()
{
    StorageModule* storageModule = &StorageModule::getInstance();
    const char* jwt = storageModule->readAt(JWT_ADDRESS);

    Serial.print("[MqttModule] Connecting to broker ");
    Serial.print(BROKER_HOST);
    Serial.print(":");
    Serial.print(BROKER_PORT);
    Serial.println("...");

    Serial.print("[MqttModule] JWT Credentials: <");
    Serial.print(jwt);
    Serial.println(">");

    mqttClient.setUsernamePassword(jwt, "");
    for (size_t i = 1; i <= 3; ++i) 
    {
        Serial.print("[MqttModule] Trying connection (");
        Serial.print(i);
        Serial.println("/3).");
        
        if (mqttClient.connect(BROKER_HOST, BROKER_PORT))
        {
            break;
        }

        Serial.print("[MqttModule] Connection failed! Error code: ");
        Serial.print(mqttClient.connectError());
        Serial.println(".");
    }

    Serial.println("[MqttModule] Connection successful!");
    Serial.print("[MqttModule] Subscribing to: ");
    Serial.println(READS);

    mqttClient.onMessage([](int messageSize) {
        MqttModule* mqttModule = &MqttModule::getInstance();
        mqttModule->onMqttMessage(messageSize);
    });

    int subStatus = mqttClient.subscribe(READS.c_str());
}

void MqttModule::onMqttMessage(int messageSize)
{
    ControlModule* controlModule = &ControlModule::getInstance();

    char receivedMessage[messageSize];
    int i = 0;
    while (mqttClient.available()) {
        receivedMessage[i] = (char) mqttClient.read();
        ++i;
    }
    String receivedString = String(receivedMessage);

    Serial.print("[MqttModule] Received MQTT Message: ");
    Serial.println(receivedString);

    if (strncmp(receivedMessage, "toggle", 6) == 0) {
        controlModule->toggle();
        String response = String("{\"message\":\"toggled\"}");

        mqttClient.beginMessage(WRITES);
        mqttClient.print(response);
        mqttClient.endMessage();
    }
}


MqttModule& MqttModule::getInstance()
{
    static MqttModule singleton;
    return singleton;
}

}