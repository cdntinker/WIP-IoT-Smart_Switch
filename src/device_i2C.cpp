#include "device_I2C.h"

void I2C_setup()
{
    // Initialising I2C
    strcpy(DEBUGtxt, "I2C");
    DEBUG_LineOut(DEBUGtxt);

    Wire.begin();

    I2C_scan();

#ifdef I2C_INA219
    INA219_setup();
#endif

#ifdef I2C_INA226
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

