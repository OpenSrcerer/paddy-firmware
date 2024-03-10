#include "src/daemon/Daemon.hpp"

// ------ Other ------
// long millisLastMeasurement = 0;
// bool lightStatus        = false;

paddy::Daemon daemon;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);


  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

  daemon.toggle(); // Move to the next state
}

void loop() {
  // if (millis() - millisLastMeasurement > 100) {
  //   millisLastMeasurement = millis();

  //   digitalWrite(2, lightStatus);
  // }

  // mqttClient.poll();
}