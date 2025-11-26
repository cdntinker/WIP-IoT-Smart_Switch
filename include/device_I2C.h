#include "Wire.h"

#include "Tinker_DEBUG.h"
extern char DEBUGtxt[256];
#include "MQTT.h" // emdedded functions for wifi and mqtt       should be cpp

extern byte I2CdevList[127];   // This should actually be a structure to hold info about the devices beyond just their addresses...

void I2C_setup();
unsigned int I2C_scan();
void I2C_identifier(uint8_t address);

#ifdef INA219_installed
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

#ifdef INA226_installed
#include "INA226.h"

void INA226_setup();
void INA226_check();
void INA226_getreadings();

float INA226_Vbus();
float INA226_Vshunt();
float INA226_Vload();
float INA226_Current();
float INA226_Power();
#endif
