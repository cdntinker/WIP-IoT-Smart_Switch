#include "device_I2C.h"

void I2C_setup()
{
    // Initialising I2C
    strcpy(DEBUGtxt, "I2C");
    DEBUG_LineOut(DEBUGtxt);

    Wire.begin();

    I2C_scan();

#ifdef INA219
    INA219_setup();
#endif
}

unsigned int I2C_scan()
{
    // The following is an I2C scanner
    unsigned int count = 0;
    for (byte i = 8; i < 120; i++)

    {

        Wire.beginTransmission(i);
        if (Wire.endTransmission() == 0)
        {
            sprintf(DEBUGtxt, "Found I2C Device:  (0x%X)", count);
            DEBUG_LineOut2(DEBUGtxt);
            sprintf(DEBUGtxt, "(0x%X)", count);
            MQTT_SendSTAT("I2C/Device", DEBUGtxt);
            count++;
            delay(1);
        }
    }
    sprintf(DEBUGtxt, "Finished I2C scanner");
    DEBUG_LineOut2(DEBUGtxt);
    sprintf(DEBUGtxt, "Found %X Device(s).", count);
    DEBUG_LineOut2(DEBUGtxt);
    sprintf(DEBUGtxt, "%d", count);
    MQTT_SendSTAT("I2C/Count", DEBUGtxt);

    return (count);
}

#ifdef INA219
Adafruit_INA219 ina219;

void INA219_setup()
{
    INA219_check();
}

void INA219_check()
{

    if (!ina219.begin())
    {
        strcpy(DEBUGtxt, "Failed to find INA219 chip");
    }
    else
    {
        strcpy(DEBUGtxt, "Found an INA219 chip");

        // Configures to INA219 to be able to measure up to 32V and 2A of current.
        // Each unit of current corresponds to 100uA, and each unit of power corresponds to 2mW.
        // Counter overflow occurs at 3.2A.
        ina219.setCalibration_32V_2A();

        // Configures to INA219 to be able to measure up to 32V and 1A of current.
        // Each unit of current corresponds to 40uA, and each unit of power corresponds to 800uW.
        // Counter overflow occurs at 1.3A
        // ina219.setCalibration_32V_1A();

        // set device to calibration which uses the highest precision for current measurement (0.1mA),
        // at the expense of only supporting 16V at 400mA max.
        // ina219.setCalibration_16V_400mA();

        INA219_getreadings();
    }
    DEBUG_LineOut2(DEBUGtxt);
    MQTT_SendSTAT("I2C/INA219", DEBUGtxt);
}

void INA219_getreadings()
{
    char Batt_state[24];
    if (INA219_Vshunt() < 0)
        strcpy(Batt_state, "Charging");
    else
        strcpy(Batt_state, "Discharging");

    sprintf(DEBUGtxt, "{\"V_bus\":\"%.3f\", \"mV_shunt\":\"%.3f\", \"V_load\":\"%.3f\", \"mA\":\"%.3f\", \"mW\":\"%.3f\", \"State\":\"%s\"}",
            INA219_Vbus(),
            INA219_Vshunt(),
            INA219_Vload(),
            INA219_Current(),
            INA219_Power(),
            Batt_state
            // "Unknown as yet"
    );

    DEBUG_LineOut(DEBUGtxt);
    MQTT_SendSTAT("I2C/INA219readings", DEBUGtxt);
}

float INA219_Vbus()
{
    return (ina219.getBusVoltage_V());
}

float INA219_Vshunt()
{
    return (ina219.getShuntVoltage_mV() / 1000);
}

float INA219_Vload()
{
    return (INA219_Vbus() + INA219_Vshunt());
}

float INA219_Current()
{
    return (ina219.getCurrent_mA());
}

float INA219_Power()
{
    return (ina219.getPower_mW());
}
#endif
