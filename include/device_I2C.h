#include "Wire.h"

#include "Tinker_DEBUG.h"
extern char DEBUGtxt[256];
#include "MQTT.h" // emdedded functions for wifi and mqtt       should be cpp

extern byte I2CdevList[127];   // This should actually be a structure to hold info about the devices beyond just their addresses...

void I2C_setup();
unsigned int I2C_scan();
void I2C_identifier0(uint8_t address);
void I2C_identifier(uint8_t DevNum, uint8_t address);

#include "I2C_INA219.h"
#include "I2C_INA226.h"
