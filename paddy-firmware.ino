#include <ArduinoMqttClient.h>
#include <ArduinoBLE.h>
#include <WiFiNINA.h>
#include <WiFiSSLClient.h>
#include "paddy_secrets.h"

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

// ------ Bluetooth Configuration ------
char WIFI_UUID[]     = SECRET_WIFI_UUID;
char SSID_UUID[]     = SECRET_SSID_UUID;
char PASS_UUID[]     = SECRET_PASS_UUID;

// ------ Bluetooth ------
BLEService bleWifiService(WIFI_UUID);
BLEStringCharacteristic bleSsidChar(SSID_UUID, BLEWrite, 32);
BLEStringCharacteristic blePassChar(PASS_UUID, BLEWrite, 32);

const char* ssidCharValue = "";
const char* passCharValue = "";

// ------ Wifi & MQTT ------
WiFiSSLClient client;
MqttClient mqttClient(client);

// ------ Other ------
long millisLastMeasurement = 0;
bool lightStatus        = true;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  // ------ Bluetooth Phase ------
  do {
    startBLE();
    getWifiCredentialsBLE();
  } while (!setupWifi(ssidCharValue, passCharValue));

  digitalWrite(LED_BUILTIN, HIGH);
  
  // ------ MQTT Phase ------
  setupMqtt();
}

void loop() {
  if (millis() - millisLastMeasurement > 500) {
    millisLastMeasurement = millis();

    lightStatus = !lightStatus;
    digitalWrite(LED_BUILTIN, lightStatus);
  }

  mqttClient.poll();
}

// ---------------------

void startBLE() {
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }
  
  // Set up BLE service and characteristics
  BLE.setLocalName("paddy_proto_03");
  BLE.setAdvertisedService(bleWifiService);
  bleWifiService.addCharacteristic(bleSsidChar);
  bleWifiService.addCharacteristic(blePassChar);
  BLE.addService(bleWifiService);
  BLE.advertise();

  Serial.println("BLE listening...");
}

void stopBLE(BLEDevice& central) {
  central.disconnect();
  BLE.stopAdvertise();
  BLE.end();
  Serial.println("BLE ended.");
}

void stopWifi() {
  clearWifiCreds();
  WiFi.disconnect();
  WiFi.end();
  Serial.println("WiFi ended.");
}

void clearWifiCreds() {
  ssidCharValue = "";
  passCharValue = "";
}

void getWifiCredentialsBLE() {
  while (1) {
    BLEDevice central = BLE.central();

    if (central) {
      Serial.print("Connected to BLE Central: ");
      Serial.println(central.address());

      while (central.connected()) {
        if (!central.connected()) {
          Serial.println("BLE Central disconnected!");
          BLE.advertise(); // Re-advertise after disconnection
        }

        if (bleSsidChar.written()) {
          ssidCharValue = strdup(bleSsidChar.value().c_str());
        }

        if (blePassChar.written()) {
          passCharValue = strdup(blePassChar.value().c_str());
        }

        if (strlen(ssidCharValue) != 0 && strlen(passCharValue) != 0) {
          stopBLE(central);

          Serial.print("SSID Retrieved: ");
          Serial.println(ssidCharValue);

          Serial.print("Pass Retrieved: ");
          Serial.println(passCharValue);

          return;
        }
      }
    }
  }
}

bool setupWifi(const char*& ssid, const char*& pass) {
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);

  if (WiFi.begin(ssid, pass) == WL_CONNECTED) {
    Serial.println("WiFi connected!");
    return true;
  } else {
    Serial.println("WiFi connection failed.");
    stopWifi();
    return false;
  }
}

void setupMqtt() {
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.print(BROKER_HOST);
  Serial.print(":");
  Serial.println(BROKER_PORT);

  mqttClient.setUsernamePassword(JWT, "");

  if (!mqttClient.connect(BROKER_HOST, BROKER_PORT)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.print("Subscribing to: ");
  Serial.println(READ_TOPIC);

  mqttClient.onMessage(onMqttMessage);
  mqttClient.subscribe(READ_TOPIC);
}

void onMqttMessage(int messageSize) {
  // use the Stream interface to print the contents
  // while (mqttClient.available()) {
  //   Serial.print((char) mqttClient.read());
  // }

  String response = String("{\"message\":\"Hello Wizzy\"}");

  mqttClient.beginMessage(WRITE_TOPIC);
  mqttClient.print(response);
  mqttClient.endMessage();
}