#include "Tinker_DEBUG.h"
#include "device_Battery.h"

#ifdef Battery_Operated

unsigned int ADCvalue = 0;
float BatteryVoltage;

void Battery_setup()
{
    pinMode(A0, INPUT);
}

unsigned int ADC_Reading()
{
    int ADCvalue = analogRead(A0);
    if (ADCvalue < 100)
        ADCvalue = 0;    // A fair indication there is no actual battery...
    return (ADCvalue);
}

float Battery_measure()
{
    BatteryVoltage = ADC_Reading() / BATTDIV;

    return (BatteryVoltage);
}

void Battery_loop()
{
    sprintf(DEBUGtxt, "Battery Voltage: %.2f", Battery_measure());
    DEBUG_LineOut2(DEBUGtxt);
}

#else
void Battery_setup()
{
}
unsigned int ADC_Reading()
{
    return (-1);
}
float Battery_measure()
{
    return (-1);
}
void Battery_loop()
{
}
#endif
