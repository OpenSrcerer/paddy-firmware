#include "DaemonSecrets.hpp"
#include "DaemonGlobals.hpp"

// ------ MQTT Configuration ------
char BROKER_HOST[]      = SECRET_BROKER_HOST;
int  BROKER_PORT        = SECRET_BROKER_PORT;

char DEVICE_SERIAL[]    = SECRET_DEVICE_SERIAL;

// ------ Bluetooth Configuration ------
char BLE_NAME[]         = SECRET_BLE_NAME;

char SERVICE_UUID[]     = SECRET_SERVICE_UUID;
char SERIAL_UUID[]      = SECRET_SERIAL_UUID;
char SSID_UUID[]        = SECRET_SSID_UUID;
char PASS_UUID[]        = SECRET_PASS_UUID;
char E_USERNAME_UUID[]  = SECRET_E_USERNAME_UUID;
char E_PASSWORD_UUID[]  = SECRET_E_PASSWORD_UUID;
char JWT_UUID[]         = SECRET_JWT_UUID;
char RESET_UUID[]       = SECRET_RESET_UUID;

// ------ Hardware Configuration ------
int  CONTROL_PIN        = 2;
int  MEASUREMENT_PIN    = 7;