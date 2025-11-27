#include "device_I2C.h"

#ifdef I2C_INA226
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
