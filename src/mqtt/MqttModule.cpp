#include "MqttModule.hpp"
#include "../control/ControlModule.hpp"
#include "../storage/StorageModule.hpp"
#include "../DaemonGlobals.hpp"

// Topics
String WRITES = String("daemon/") + String(DEVICE_SERIAL) + "/v1/writes";
String READS  = String("daemon/") + String(DEVICE_SERIAL) + "/v1/reads/#";

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
    mqttClient.setId(String("paddy-daemon-") + DEVICE_SERIAL);
    mqttClient.setCleanSession(false);

    for (size_t i = 1; i <= 3; ++i) 
    {
        Serial.print("[MqttModule] Trying connection (");
        Serial.print(i);
        Serial.println("/3)");
        
        if (mqttClient.connect(BROKER_HOST, BROKER_PORT))
        {
            break;
        }

        if (i == 2) {
            Serial.print("[MqttModule] Connection failed! Error code: ");
            Serial.print(mqttClient.connectError());

            return;
        }
    }

    Serial.println("[MqttModule] Connection successful!");
    Serial.print("[MqttModule] Subscribing to: ");
    Serial.println(READS);

    mqttClient.onMessage([](int messageSize) {
        (&MqttModule::getInstance())->onMqttMessage(messageSize);
    });

    int subStatus = mqttClient.subscribe(READS, 2);
    Serial.println("[MqttModule] Subscription status: " + String(subStatus));

    // If you arrived here, subscription succeeded, everything ok!
    // Not sure about the statuses, 0 & 1 seem correct, there are no docs...
    if (subStatus == 0 || subStatus == 1)
    {
        connectionSucceeded = true;
    }
}

void MqttModule::stopMqtt()
{
    mqttClient.unsubscribe(READS);
    mqttClient.stop();

    deviceRotated = false;

    Serial.println("[MqttModule] Connection ended.");
}

void MqttModule::onMqttMessage(int messageSize)
{
    ControlModule* controlModule = &ControlModule::getInstance();
    StorageModule* storageModule = &StorageModule::getInstance();

    String topic = mqttClient.messageTopic();
    
    char payload[messageSize];
    int i = 0;
    while (mqttClient.available() && messageSize > 0) 
    {
        payload[i] = (char) mqttClient.read();
        ++i;
    }
    payload[i] = '\0'; // Null-terminate the payload

    Serial.println(String("[MqttModule] <") + String(topic) + String("> ") 
        + String("[") + String(messageSize) + String("]: ") + String(payload));

    if (topic.endsWith(String("on")))
    { // Turn device on
        controlModule->on();
    }
    else if(topic.endsWith(String("off")))
    { // Turn device off
        controlModule->off();
    }
    else if (topic.endsWith(String("toggle"))) 
    { // Toggle device
        controlModule->toggle();
    }
    else if (topic.endsWith(String("reset"))) 
    { // Reset device completely
        deviceReset = true;
    }
    else if (topic.endsWith(String("rotate")))
    { // Rotate JWT when is near expiration
        deviceRotated = true;
        storageModule->writeAt(payload, JWT_ADDRESS);
    }
}

void MqttModule::sendMessage(const char* action, const String* message)
{
    Serial.print("[MqttModule] Sending <" + String(action) + ">: [");

    mqttClient.beginMessage(WRITES + String("/") + action);
    if (message != nullptr)
    {
        Serial.print(*message);
        mqttClient.print(*message);
    }

    Serial.println("]");
    mqttClient.endMessage();
}


MqttModule& MqttModule::getInstance()
{
    static MqttModule singleton;
    return singleton;
}

}