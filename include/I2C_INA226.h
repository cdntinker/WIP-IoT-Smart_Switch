
#include "Tinker_DEBUG.h"
extern char DEBUGtxt[256];
#include "MQTT.h" // emdedded functions for wifi and mqtt       should be cpp

#ifdef I2C_INA226
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
