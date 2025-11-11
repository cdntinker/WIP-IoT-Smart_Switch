#include "Tinker_DEBUG.h"
#include "device_Battery.h"

/*
 * Wemos battery shield, measure Vbat
 * add 100k between Vbat and ADC
 * Voltage divider of 100k+220k over 100k
 * gives 100/420k
 * ergo 4.2V -> 1Volt
 * Max input on A0=1Volt ->1023
 * 4.2*(Raw/1023)=Vbat
 */

unsigned int BatteryRaw = 0;
float BatteryVoltage = 0.0;

void Battery_setup()
{

    pinMode(A0, INPUT);
}

unsigned int Battery_Raw()
{
    return (analogRead(A0));
}

float Battery_measure()
{
    BatteryVoltage = Battery_Raw() / BATTDIV;

    return (BatteryVoltage);
}

void Battery_loop()
{
    sprintf(DEBUGtxt, "Battery Voltage: %.2f", Battery_measure());

    DEBUG_LineOut2(DEBUGtxt);
}