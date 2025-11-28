#include "device_I2C.h"

#include "INA226.h"

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

// char poop[64];
char I2C_Whatsit[32];

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
            sprintf(DEBUGtxt, "Unknown error at 0x%2X)", I2Caddress);
            DEBUG_LineOut2(DEBUGtxt);
            MQTT_SendNOTI("I2C", DEBUGtxt);
        }
    }

    sprintf(DEBUGtxt, "Found %d Device(s).", nDevices);
    DEBUG_LineOut2(DEBUGtxt);
    MQTT_SendNOTI("I2C", DEBUGtxt);

    for (byte i = 0; i < nDevices; i++)
    {
        // This'd be an awesome place to stuff in code to determine what each I2C device actually is...
        I2C_identifier(i, I2CdevList[i]);

        sprintf(DEBUGtxt, "Found I2C Device @: 0x%2X (%s)", I2CdevList[i], I2C_Whatsit);
        DEBUG_LineOut2(DEBUGtxt);
        MQTT_SendNOTI("I2C", DEBUGtxt);
    }

    return (nDevices);
}

void I2C_identifier(uint8_t DevNum, uint8_t address)
{
    INA226 INA226_test = INA226(address);           // This should be changed to a more generic library
    if (!INA226_test.begin())
    {
        sprintf(DEBUGtxt, "I2C Device #%d @ 0x%X FAILED!!!", DevNum, address);
        DEBUG_LineOut2(DEBUGtxt);
    }
    else
    {
        uint16_t ManufacturerID = INA226_test.getManufacturerID();
        uint16_t DieID = INA226_test.getDieID();

        sprintf(DEBUGtxt, "I2C Device #%d @ 0x%X SUCCEEDED!!! [0x%04X:0x%04X]",
                DevNum, address, ManufacturerID, DieID);
        DEBUG_LineOut2(DEBUGtxt);

        sprintf(I2C_Whatsit, "IHNFC... [0x%04X:0x%04X]",
                ManufacturerID, DieID);
        // Just in case INA226_test returns something we don't yet know

        if ((ManufacturerID == 0x0000))
            if ((DieID == 0x00FF))
                strcpy(I2C_Whatsit, "MCP23017"); // 16-bit I/O expander

        if ((ManufacturerID == 0xF6F6))
            if ((DieID == 0xF7F7))
                strcpy(I2C_Whatsit, "PCF8574"); // 8-bit I/O expander

        if ((ManufacturerID == 0x5449))
            if ((DieID == 0x2260))
                strcpy(I2C_Whatsit, "INA226"); // high-precision, 16-bit, digital current shunt and power monitor

        if ((ManufacturerID == 0x8000))
            if ((DieID == 0x0000))
                strcpy(I2C_Whatsit, "ADS1115"); // 16-bit ADC

        if ((ManufacturerID == 0x4343))
            if ((DieID == 0x4343))
                strcpy(I2C_Whatsit, "SSD1306"); // CMOS OLED/PLED driver

        if (ManufacturerID == 0x2000)
            if ((DieID == 0x8214) || (DieID == 0xC20E) || (DieID == 0xFC06))
                strcpy(I2C_Whatsit, "INA219"); // high-side current shunt and power monitor
    }
}
