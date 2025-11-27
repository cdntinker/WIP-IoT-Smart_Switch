#include <Arduino.h>

#define MQTT_BUFFER_SIZE (100) // This number is arbitrary

void MQTT_SendSTAT(const char *Topic, const char *Message);
void MQTT_SendNOTI(const char *Topic, const char *Message);
void MQTT_SendTELE(const char *Topic, const char *Message);

#include "Tinker_DEBUG.h"
extern char DEBUGtxt[256];

#include "device_Buttons.h"
// #include "device_LEDs.h"
// #include "device_Relays.h"
#include "device_I2C.h"

#include "DEVICE_SPECIFIC.h"

void SmartSwitch_init()
{
    DEBUG_Init("SmartSwitch");

#ifdef I2C_enabled
    I2C_setup();
#endif

#ifdef Battery_Operated
    /*****  Battery *****/
    Battery_setup();
#ifdef BATDIV
    sprintf(DEBUGtxt, "Battery: (on A0)");
    DEBUG_LineOut(DEBUGtxt);
    sprintf(DEBUGtxt, " ADC raw: %d", ADC_Reading());
    DEBUG_LineOut2(DEBUGtxt);
    sprintf(DEBUGtxt, " initial: %.3fV", Battery_measure());
    DEBUG_LineOut2(DEBUGtxt);
#endif

#ifdef I2C_INA219
    sprintf(DEBUGtxt, "Battery: (using INA219)");
    DEBUG_LineOut(DEBUGtxt);
#endif

#ifdef I2C_INA226
    sprintf(DEBUGtxt, "Battery: (using INA226)");
    DEBUG_LineOut(DEBUGtxt);
#endif

#endif

#ifdef SmartSwitch_Relays
    /*****  Relays  *****/
    Relay_setup();
#endif

#ifdef SmartSwitch_LEDs
    /*****  LEDs  *****/
    LED_setup();
#endif

#ifdef SmartSwitch_Buttons
    /*****  Buttons  *****/
    Button_setup();
#endif

    /*****  Switches  *****/

    // Button_init();

}

void SmartSwitch_loop()
{
    Button_loop();
}

// Handle incoming MQTT messages for the SmartSwitch functionality
char StatusMessage[12];

void SmartSwitch_MQTT_in(const char *MQTT_command, const char *MQTT_msg_in)
{
    String TheTopic = MQTT_command;
    char NotiMSG[32];
    int CTRbegin, CTRfinish;

    if (TheTopic.startsWith("/Power"))
    {
        TheTopic.remove(0, 6);
        if (TheTopic == "")
        {
            CTRbegin = 0;
            CTRfinish = GPIO_Relay_COUNT;
            MQTT_SendNOTI("triggered", "All Da Power!");
        }
        else
        {
            CTRbegin = TheTopic.toInt();
            CTRfinish = TheTopic.toInt() + 1;
            sprintf(NotiMSG, "Power%s", TheTopic.c_str());
            MQTT_SendNOTI("triggered", NotiMSG);
        }

        for (int CTR = CTRbegin; CTR < CTRfinish; CTR++)
        {
            if ((unsigned int)TheTopic.toInt() < GPIO_Relay_COUNT)
            {
                if (strcmp(MQTT_msg_in, "on") == 0)
                    DEVICE_RELAY(CTR, HIGH);
                if (strcmp(MQTT_msg_in, "off") == 0)
                    DEVICE_RELAY(CTR, LOW);
                if (strcmp(MQTT_msg_in, "toggle") == 0)
                    DEVICE_RELAY_TOGGLE(CTR);
            }
            else
                MQTT_SendNOTI("triggered", "Unknown Power!");
        }
    }

    else if (TheTopic.startsWith("/LED"))
    {
        TheTopic.remove(0, 4);
        if (TheTopic == "")
        {
            CTRbegin = 0;
            CTRfinish = GPIO_LED_COUNT;
            MQTT_SendNOTI("triggered", "All Da LEDs!");
        }
        else
        {
            CTRbegin = TheTopic.toInt();
            CTRfinish = TheTopic.toInt() + 1;
            sprintf(NotiMSG, "LED%s", TheTopic.c_str());
            MQTT_SendNOTI("triggered", NotiMSG);
        }

        for (int CTR = CTRbegin; CTR < CTRfinish; CTR++)
        {
            if ((unsigned int)TheTopic.toInt() < GPIO_LED_COUNT)
            {
                if (strcmp(MQTT_msg_in, "on") == 0)
                    DEVICE_LED(CTR, HIGH);
                if (strcmp(MQTT_msg_in, "off") == 0)
                    DEVICE_LED(CTR, LOW);
                if (strcmp(MQTT_msg_in, "toggle") == 0)
                    DEVICE_LED_TOGGLE(CTR);
            }
            else
                MQTT_SendNOTI("triggered", "Unknown LED!");
        }
    }

    else if (strcmp(MQTT_command, "/Status") == 0) ///// Needs complete rewrite
    {
        MQTT_SendNOTI("triggered", "Status!!!");
        DEBUG_LineOut("Status Requested");
        if (strcmp(MQTT_msg_in, "Power") == 0)
        {
            DEBUG_LineOut2("Power");
            MQTT_SendSTAT("Power", GPIO_Relay_STATE[0] ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "LED00") == 0)
        {
            DEBUG_LineOut2("LED00");
            MQTT_SendSTAT("LED00", GPIO_LED_STATE[0] ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "LED01") == 0)
        {
            DEBUG_LineOut2("LED01");
            MQTT_SendSTAT("LED01", GPIO_LED_STATE[0] ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "LNKLD") == 0)
        {
            DEBUG_LineOut2("LNKLD");
            MQTT_SendSTAT("LNKLD", GPIO_LED_STATE[1] ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "All") == 0)
        {
            DEBUG_LineOut2("All");
            MQTT_SendSTAT("Power", GPIO_Relay_STATE[0] ? "ON" : "OFF");
            MQTT_SendSTAT("LED01", GPIO_LED_STATE[0] ? "ON" : "OFF");
            MQTT_SendSTAT("LNKLD", GPIO_LED_STATE[1] ? "ON" : "OFF");
            sprintf(StatusMessage, "%f", Battery_measure());
            MQTT_SendSTAT("Battery", StatusMessage);
        }
        else if (strcmp(MQTT_msg_in, "Battery") == 0)
        {
            DEBUG_LineOut2("Battery");
            sprintf(DEBUGtxt, " ADC raw: %d", ADC_Reading());
            DEBUG_LineOut2(DEBUGtxt);
            sprintf(DEBUGtxt, " initial: %fV", Battery_measure());
            DEBUG_LineOut2(DEBUGtxt);
            sprintf(StatusMessage, "%d", ADC_Reading());
            MQTT_SendSTAT("ADC", StatusMessage);
            sprintf(StatusMessage, "%.3f", Battery_measure());
            MQTT_SendSTAT("Battery", StatusMessage);
        }
        else if (strcmp(MQTT_msg_in, "I2C") == 0)
        {
            DEBUG_LineOut2("I2C");
            I2C_scan();
        }
#ifdef I2C_INA219
        else if (strcmp(MQTT_msg_in, "INA219") == 0)
        {
            DEBUG_LineOut2("INA219");
            INA219_check();
        }
#endif
#ifdef I2C_INA226
        else if (strcmp(MQTT_msg_in, "INA226") == 0)
        {
            DEBUG_LineOut2("INA226");
            INA226_setup();
        }
#endif
        // else if (strcmp(MQTT_msg_in, "All") == 0)
    }

    else // Ya cornfoozed me!
    {
        DEBUG_Trouble("Dunno Whatcha want...");
        MQTT_SendNOTI("Error", "Dunno Whatcha want...");
    }
}
