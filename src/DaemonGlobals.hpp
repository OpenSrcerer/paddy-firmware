#ifndef DAEMON_GLOBALS_HPP
#define DAEMON_GLOBALS_HPP

// ------ MQTT Configuration ------
extern char   BROKER_HOST[];
extern int    BROKER_PORT;

extern char   DEVICE_SERIAL[];
extern int    PING_INTERVAL;

// ------ Bluetooth Configuration ------
extern char   BLE_NAME[];           // Name that pops up on the device when looking up bluetooth

extern char   SERVICE_UUID[];       // BLE UUIDs for different funcs below. This is the main one.
extern char   SERIAL_UUID[];
extern char   SSID_UUID[];
extern char   PASS_UUID[];
extern char   E_USERNAME_UUID[];
extern char   E_PASSWORD_UUID[];
extern char   JWT_UUID[];
extern char   RESET_UUID[];

// ------ Hardware Configuration ------
extern int    CONTROL_PIN;          // Arduino pin to control the relay with.
extern int    MEASUREMENT_PIN;      // Measurement pin to read CT

// ------ Power Measurement Configuration ------
extern int    CT_SAMPLES;           // Current samples per second
extern float  CT_CALIBRATE;         // Calibrates the CT readings to be sampled.
extern float  CT_VOLTAGE;           // The voltage to measure with (240V or 120V grid, for instance)
extern float  CT_LINEAR_SHIFT;      // Sometimes the calibrate moves the y-axis of the voltage up. You can drag it down with this.

#endif
