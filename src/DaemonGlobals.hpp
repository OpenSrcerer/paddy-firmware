#ifndef DAEMON_GLOBALS_HPP
#define DAEMON_GLOBALS_HPP

// ------ MQTT Configuration ------
// Broker
extern char BROKER_HOST[];
extern int  BROKER_PORT;

extern char DEVICE_SERIAL[];

// ------ Bluetooth Configuration ------
extern char BLE_NAME[];

extern char SERVICE_UUID[];
extern char SERIAL_UUID[];
extern char SSID_UUID[];
extern char PASS_UUID[];
extern char E_USERNAME_UUID[];
extern char E_PASSWORD_UUID[];
extern char JWT_UUID[];

#endif