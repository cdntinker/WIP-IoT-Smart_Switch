#include "device_I2C.h"

void I2C_setup()
{
    // Initialising I2C
    strcpy(DEBUGtxt, "I2C");
    DEBUG_LineOut(DEBUGtxt);

    Wire.begin();

    I2C_scan();

#ifdef INA219_installed
    INA219_setup();
#endif

#ifdef INA226_installed
    INA226_setup();
#endif
}

byte I2CdevList[127]; // This should actually be a structure to hold info about the devices beyond just their addresses...

    char poop[64];

unsigned int I2C_scan()
{
    byte I2Cerr, I2Caddress;
    unsigned int nDevices = 0;
    for (I2Caddress = 1; I2Caddress < 127; I2Caddress++)
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(I2Caddress);
        I2Cerr = Wire.endTransmission();

        if (I2Cerr == 0)
        {
            I2CdevList[nDevices] = I2Caddress;

            nDevices++;
        }
        else if (I2Cerr == 4)
        {
            sprintf(DEBUGtxt, "Unknown error at address 0x%2X)", I2Caddress);
            DEBUG_LineOut2(DEBUGtxt);

        }
    }

    for (byte i = 0; i < nDevices; i++)
    {
        // This'd be an awesome place to stuff in code to determine what each I2C device actually is...
        I2C_identifier(I2CdevList[i]);

        sprintf(DEBUGtxt, "Found I2C Device @ address:  0x%2X (%s)", I2CdevList[i], poop);
        DEBUG_LineOut2(DEBUGtxt);
            // I2C_identifier(I2CdevList[i]);
    }
    sprintf(DEBUGtxt, "Found %d Device(s).", nDevices);
    DEBUG_LineOut2(DEBUGtxt);
    sprintf(DEBUGtxt, "%d", nDevices);
    MQTT_SendSTAT("I2C/Count", DEBUGtxt);

    return (nDevices);
}


void I2C_identifier(uint8_t address)
{
    // For some hints: https://learn.adafruit.com/i2c-addresses/the-list
    // and https://github.com/adafruit/I2C_Addresses
    if (address <= 0x07)                        strcpy(poop, "reserved");
    if (address >= 0x08 && address <= 0x0A)     strcpy(poop, "No Clue");
    if (address == 0x0B)                        strcpy(poop, "LC709203F");

    
    if (address >= 0x20 && address <= 0x27)     strcpy(poop, "MCP23008 MCP23017 PCF8574");
    if (address == 0x21 || address == 0x22)     strcpy(poop, "SAA4700");

    if (address >= 0x30 && address <= 0x3F)     strcpy(poop, "PCF8574");
    if (address >= 0x3c && address <= 0x3d)     strcpy(poop, "PCF8578");

    if (address == 0x40)                        strcpy(poop, "SHT21/SI7021 INI219/INI226");
    if (address >= 0x41 && address <= 0x4F)     strcpy(poop, "INI219/INI226");

    if (address >= 0x50 && address <= 0x57)     strcpy(poop, "AT24C32"); // on some DS3231 breakout boards there is this IC at 0x57

    if (address == 0x68)                        strcpy(poop, "DS3231");
    if (address >= 0x68 && address <= 0x6b)     strcpy(poop, "PCF8573");

    if (address >= 0x70 && address <= 0x77)     strcpy(poop, "HT16K33 TCA9548");
    if (address >= 0x76 && address <= 0x77)     strcpy(poop, "BME280 BME680 BMP280");

    if (address >= 0x78 && address <= 0x7B)     strcpy(poop, "Reserved for 10-bit I2C addressing");
    if (address >= 0x7C && address <= 0x7F)     strcpy(poop, "Reserved for future purposes");
}

#ifdef INA219_installed
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

        // INA219_getreadings();
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

#ifdef INA226_installed
#define INA_COUNT 4

INA226 INA[INA_COUNT] =
    {
        INA226(I2CdevList[0]),
        INA226(I2CdevList[1]),
        INA226(I2CdevList[2]),
        INA226(I2CdevList[3])};

// bool failed = false;

void INA226_setup()
{

    sprintf(DEBUGtxt, "INA226_LIB_VERSION: %s", (char *)INA226_LIB_VERSION);
    DEBUG_LineOut(DEBUGtxt);

    for (int ID = 0; ID < INA_COUNT; ID++)
    {
        if (!INA[ID].begin())
        {
            // failed = true;
            sprintf(DEBUGtxt, "INA226 %d (%X) FAILED!!!", ID, I2CdevList[ID]);
            DEBUG_LineOut2(DEBUGtxt);
        }
        else
        {
            // failed = false;
            sprintf(DEBUGtxt, "INA226 %d (%X) SUCCEEDED!!! [%d : %d]", ID, I2CdevList[ID], INA[ID].getManufacturerID(), INA[ID].getDieID());
            DEBUG_LineOut2(DEBUGtxt);

        }
    }
    // if (failed)
    // {
    //     Serial.println("One or more INA could not connect. Fix and Reboot");
    //     // while (1)
    //         // ;
    // }
//  getManufacturerID() ;   // should return 0x5449
//  getDieID()          ;   // should return 0x2260

}

void INA226_check()
{
}

void INA226_getreadings()
{
}

float INA226_Vbus()
{
    return (0);
}

float INA226_Vshunt()
{
    return (0);
}

float INA226_Vload()
{
    return (0);
}

float INA226_Current()
{
    return (0);
}

float INA226_Power()
{
    return (0);
}

#endif
