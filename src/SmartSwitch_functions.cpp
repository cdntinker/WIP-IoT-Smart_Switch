#include <Arduino.h>

#include "Tinker_SmartSwitch.h"
// #include "Tinker_MQTT.h"
#define MQTT_BUFFER_SIZE (100) // This number is arbitrary

void MQTT_SendSTAT(const char *Topic, const char *Message);
void MQTT_SendNOTI(const char *Topic, const char *Message);
void MQTT_SendTELE(const char *Topic, const char *Message);

#include "Tinker_DEBUG.h"
extern char DEBUGtxt[92];

// #include "device_Buttons.h"
// #include "device_LEDs.h"
// #include "device_Relays.h"
#include "DEVICE_SPECIFIC.h"

void SmartSwitch_init()
{
    DEBUG_Init("SmartSwitch");

    String OOGABOOGA = "";

    /*****  Relays  *****/
    Relay_setup();
    sprintf(DEBUGtxt, " Relays: %2d", GPIO_Relay_COUNT);
    DEBUG_LineOut(DEBUGtxt);
    OOGABOOGA = "GPIOs: ";
    for (unsigned int ctr = 0; ctr < GPIO_Relay_COUNT; ctr++)
    {
        OOGABOOGA += ctr;
        OOGABOOGA += "=";
        OOGABOOGA += GPIO_Relay_PINS[ctr];
        OOGABOOGA += " ";
    }
    DEBUG_LineOut2(OOGABOOGA.c_str());

    /*****  Buttons  *****/
    Button_setup();
    sprintf(DEBUGtxt, "Buttons: %2d", ButtonCount);
    DEBUG_LineOut(DEBUGtxt);
    OOGABOOGA = "GPIOs: ";
    for (int ctr = 0; ctr < ButtonCount; ctr++)
    {
        OOGABOOGA += ctr;
        OOGABOOGA += "=";
        OOGABOOGA += SmartSwitch_ButtonPin[ctr];
        OOGABOOGA += " ";
    }
    DEBUG_LineOut2(OOGABOOGA.c_str());

    /*****  Switches  *****/

    /*****  LEDs  *****/
    LED_setup();
    sprintf(DEBUGtxt, "   LEDs: %2d", GPIO_LED_COUNT);
    DEBUG_LineOut(DEBUGtxt);
    OOGABOOGA = "GPIOs: ";
    for (unsigned int ctr = 0; ctr < GPIO_LED_COUNT; ctr++)
    {
        OOGABOOGA += ctr;
        OOGABOOGA += "=";
        OOGABOOGA += GPIO_LED_PINS[ctr];
        OOGABOOGA += " ";
    }
    DEBUG_LineOut2(OOGABOOGA.c_str());

    Button_init();
}

// Handle incoming MQTT messages for the SmartSwitch functionality

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
            if ((unsigned int) TheTopic.toInt() < GPIO_Relay_COUNT)
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
            if ((unsigned int) TheTopic.toInt() < GPIO_LED_COUNT)
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
            MQTT_SendSTAT("Power", GPIO_Relay_STATE[0] ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "LED01") == 0)
        {
            MQTT_SendSTAT("LED01", GPIO_LED_STATE[0] ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "LNKLD") == 0)
        {
            MQTT_SendSTAT("LNKLD", GPIO_LED_STATE[1] ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "All") == 0)
        {
            MQTT_SendSTAT("Power", GPIO_Relay_STATE[0] ? "ON" : "OFF");
            MQTT_SendSTAT("LED01", GPIO_LED_STATE[0] ? "ON" : "OFF");
            MQTT_SendSTAT("LNKLD", GPIO_LED_STATE[1] ? "ON" : "OFF");
        }
        // else if (strcmp(MQTT_msg_in, "All") == 0)
    }

    else // Ya cornfoozed me!
    {
        DEBUG_Trouble("Dunno Whatcha want...");
        MQTT_SendNOTI("Error", "Dunno Whatcha want...");
    }
}
