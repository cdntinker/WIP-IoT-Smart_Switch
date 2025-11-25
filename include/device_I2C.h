#include "Wire.h"

#include "Tinker_DEBUG.h"
extern char DEBUGtxt[256];
#include "MQTT.h" // emdedded functions for wifi and mqtt       should be cpp

void I2C_setup();
unsigned int I2C_scan();

#ifdef INA219
#include "Adafruit_INA219.h"

void INA219_setup();
void INA219_check();
void INA219_getreadings();

float INA219_Vbus();
float INA219_Vshunt();
float INA219_Vload();
float INA219_Current();
float INA219_Power();
#endif
