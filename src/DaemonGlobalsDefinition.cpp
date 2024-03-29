#include "DaemonSecrets.hpp"
#include "DaemonGlobals.hpp"

// ------ MQTT Configuration ------
char BROKER_HOST[]      = SECRET_BROKER_HOST;
int  BROKER_PORT        = SECRET_BROKER_PORT;

char DEVICE_SERIAL[]    = SECRET_DEVICE_SERIAL;
int  PING_INTERVAL      = 60000; // ms
int  MEASURE_INTERVAL   = 10000; // ms

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
int  MEASUREMENT_PIN    = (14ul) + 7;

// ------ Power Measurement Configuration ------
int    CT_SAMPLES       = 1676;
float  CT_CALIBRATE     = 25;   
float  CT_VOLTAGE       = 238.1;     
float  CT_LINEAR_SHIFT  = 37;