#include <Arduino.h>

#include "Tinker_SmartSwitch.h"
// #include "Tinker_MQTT.h"
#define MQTT_BUFFER_SIZE (100) // This number is arbitrary

void MQTT_SendSTAT(const char *Topic, const char *Message);
void MQTT_SendNOTI(const char *Topic, const char *Message);
void MQTT_SendTELE(const char *Topic, const char *Message);

#include "Tinker_DEBUG.h"
extern char DEBUGtxt[48];

int SmartSwitch_RelayPin[4];
bool SmartSwitch_Relay_STATE[4];
int RelayCount = 0;

int SmartSwitch_LEDPin[4];
bool SmartSwitch_LED_STATE[4];
int LEDCount = 0;

int SmartSwitch_ButtonPin[4];
int ButtonCount = 0;

void SmartSwitch_init()
{
    DEBUG_Init("SmartSwitch");

/*****  Relays  *****/
#ifdef SmartSwitch_RELAY00
    SmartSwitch_RelayPin[RelayCount] = SmartSwitch_RELAY00;
    pinMode(SmartSwitch_RelayPin[RelayCount], OUTPUT);
    RelayCount++;
#endif
#ifdef SmartSwitch_RELAY01
    SmartSwitch_RelayPin[RelayCount] = SmartSwitch_RELAY01;
    pinMode(SmartSwitch_RelayPin[RelayCount], OUTPUT);
    RelayCount++;
#endif
#ifdef SmartSwitch_RELAY02
    SmartSwitch_RelayPin[RelayCount] = SmartSwitch_RELAY02;
    pinMode(SmartSwitch_RelayPin[RelayCount], OUTPUT);
    RelayCount++;
#endif
#ifdef SmartSwitch_RELAY03
    SmartSwitch_RelayPin[RelayCount] = SmartSwitch_RELAY03;
    pinMode(SmartSwitch_RelayPin[RelayCount], OUTPUT);
    RelayCount++;
#endif

/*****  Buttons  *****/
#ifdef SmartSwitch_BUTTN00
    SmartSwitch_ButtonPin[ButtonCount] = SmartSwitch_BUTTN00;
    pinMode(SmartSwitch_ButtonPin[ButtonCount], INPUT);
    ButtonCount++;
#endif
#ifdef SmartSwitch_BUTTN01
    SmartSwitch_ButtonPin[ButtonCount] = SmartSwitch_BUTTN01;
    pinMode(SmartSwitch_ButtonPin[ButtonCount], INPUT);
    ButtonCount++;
#endif
#ifdef SmartSwitch_BUTTN02
    SmartSwitch_ButtonPin[ButtonCount] = SmartSwitch_BUTTN02;
    pinMode(SmartSwitch_ButtonPin[ButtonCount], INPUT);
    ButtonCount++;
#endif
#ifdef SmartSwitch_BUTTN03
    SmartSwitch_ButtonPin[ButtonCount] = SmartSwitch_BUTTN03;
    pinMode(SmartSwitch_ButtonPin[ButtonCount], INPUT);
    ButtonCount++;
#endif

/*****  LEDs  *****/
#ifdef SmartSwitch_LED00
    SmartSwitch_LEDPin[LEDCount] = SmartSwitch_LED00;
    pinMode(SmartSwitch_LEDPin[LEDCount], OUTPUT);
    LEDCount++;
#endif
#ifdef SmartSwitch_LED01
    SmartSwitch_LEDPin[LEDCount] = SmartSwitch_LED01;
    pinMode(SmartSwitch_LEDPin[LEDCount], OUTPUT);
    LEDCount++;
#endif
#ifdef SmartSwitch_LED02
    SmartSwitch_LEDPin[2LEDCount] = SmartSwitch_LED02;
    pinMode(SmartSwitch_LEDPin[LEDCount], OUTPUT);
    LEDCount++;
#endif
#ifdef SmartSwitch_LED03
    SmartSwitch_LEDPin[LEDCount] = SmartSwitch_LED03;
    pinMode(SmartSwitch_LEDPin[LEDCount], OUTPUT);
    LEDCount++;
#endif

String OOGABOOGA = "";

sprintf(DEBUGtxt, " Relays: %2d", RelayCount);
DEBUG_LineOut(DEBUGtxt);
OOGABOOGA = "GPIOs: ";
    for (int ctr = 0; ctr < RelayCount; ctr++)
    {
        OOGABOOGA += ctr;
        OOGABOOGA += "=";
        OOGABOOGA += SmartSwitch_RelayPin[ctr];
        OOGABOOGA += " ";
    }
    DEBUG_LineOut2(OOGABOOGA.c_str());

    // Serial.println(")");

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

sprintf(DEBUGtxt, "   LEDs: %2d", LEDCount);
DEBUG_LineOut(DEBUGtxt);
OOGABOOGA = "GPIOs: ";
    for (int ctr = 0; ctr < LEDCount; ctr++)
    {
        OOGABOOGA += ctr;
        OOGABOOGA += "=";
        OOGABOOGA += SmartSwitch_LEDPin[ctr];
        OOGABOOGA += " ";
    }
    DEBUG_LineOut2(OOGABOOGA.c_str());
}

// Handle button press
void SmartSwitch_Button(int ButtonNum)
{
}

String SmartSwitch_TurnOn;
String SmartSwitch_TurnOff;

// Turn relay on/off
void SmartSwitch_Relay(int RelayNum, bool OnOff)
{
    char MQTT_Topic[16];
    sprintf(MQTT_Topic, "Power%02d", RelayNum);

    DEBUG_SectionTitle("SmartSwitch Action");
    if (OnOff)
    {
        digitalWrite(SmartSwitch_RelayPin[RelayNum], HIGH);
        SmartSwitch_Relay_STATE[RelayNum] = HIGH;
        SmartSwitch_TurnOn = "ButtonHere";
        SmartSwitch_TurnOff = "ButtonClickable";
        MQTT_SendSTAT(MQTT_Topic, "ON");
        sprintf(DEBUGtxt, "Relay %02d (%d) ON", RelayNum, SmartSwitch_RelayPin[RelayNum]);
        DEBUG_LineOut(DEBUGtxt);
    }
    else
    {
        digitalWrite(SmartSwitch_RelayPin[RelayNum], LOW);
        SmartSwitch_Relay_STATE[RelayNum] = LOW;
        SmartSwitch_TurnOn = "ButtonClickable";
        SmartSwitch_TurnOff = "ButtonHere";
        MQTT_SendSTAT(MQTT_Topic, "OFF");
        sprintf(DEBUGtxt, "Relay %02d (%d) OFF", RelayNum, SmartSwitch_RelayPin[RelayNum]);
        DEBUG_LineOut(DEBUGtxt);
    }
}

// Turn relay on/off
void SmartSwitch_Toggle(int RelayNum)
{
    DEBUG_SectionTitle("SmartSwitch Action");
    sprintf(DEBUGtxt, "Relay %02d TOGGLE", RelayNum);
    DEBUG_LineOut(DEBUGtxt);
    SmartSwitch_Relay(RelayNum, !SmartSwitch_Relay_STATE[RelayNum]);
}

// Turn LED on/off
void SmartSwitch_LED(int LEDNum, bool OnOff)
{
    char MQTT_Topic[16];
    sprintf(MQTT_Topic, "LED%02d", LEDNum);

    if (OnOff)
    {
        DEBUG_LineOut("LED ON");
        digitalWrite(SmartSwitch_LEDPin[LEDNum], HIGH);
        SmartSwitch_LED_STATE[LEDNum] = HIGH;
        MQTT_SendSTAT(MQTT_Topic, "ON");
    }
    else
    {
        DEBUG_LineOut("LED OFF");
        digitalWrite(SmartSwitch_LEDPin[LEDNum], LOW);
        SmartSwitch_LED_STATE[LEDNum] = LOW;
        MQTT_SendSTAT(MQTT_Topic, "OFF");
    }
}

// Turn relay on/off
void SmartSwitch_LED_Toggle(int LEDNum)
{
    DEBUG_SectionTitle("SmartSwitch Action");
    sprintf(DEBUGtxt, "LED %02d TOGGLE", LEDNum);
    DEBUG_LineOut(DEBUGtxt);
    SmartSwitch_LED(LEDNum, !SmartSwitch_LED_STATE[LEDNum]);
}

#if defined(SmartSwitch) && !defined(TestCode)
void MQTT_HandleMessages(const char *Topic, const char Message[MQTT_BUFFER_SIZE])
{
    if (strcmp(Topic, "/Power") == 0)
    {
        // MQTT_SendTELE(Topic, Topic);
        MQTT_SendNOTI("triggered", "Power!!!");
        if (strcmp(Message, "on") == 0)
            SmartSwitch_Relay(HIGH);
        if (strcmp(Message, "off") == 0)
            SmartSwitch_Relay(LOW);
        if (strcmp(Message, "toggle") == 0)
            SmartSwitch_Toggle();
        // SmartSwitch_Relay(!SmartSwitch_RLY01_STATE);
    }
    else if (strcmp(Topic, "/LED01") == 0)
    {
        // MQTT_SendTELE(Topic, Topic);
        MQTT_SendNOTI("triggered", "LED01!!!");
        if (strcmp(Message, "on") == 0)
            SmartSwitch_LED(HIGH);
        if (strcmp(Message, "off") == 0)
            SmartSwitch_LED(LOW);
        if (strcmp(Message, "toggle") == 0)
            SmartSwitch_LED(!SmartSwitch_LED01_STATE);
    }
    else if (strcmp(Topic, "/LED02") == 0)
    {
        // MQTT_SendTELE(Topic, Topic);
        MQTT_SendNOTI("triggered", "LED02!!!");
        if (strcmp(Message, "on") == 0)
            SmartSwitch_LINKLED(HIGH);
        if (strcmp(Message, "off") == 0)
            SmartSwitch_LINKLED(LOW);
        if (strcmp(Message, "toggle") == 0)
            SmartSwitch_LINKLED(!SmartSwitch_LED02_STATE);
    }
    else if (strcmp(Topic, "/Status") == 0)
    {
        MQTT_SendNOTI("triggered", "Status!!!");
        DEBUG_LineOut("Status Requested");
        if (strcmp(Message, "Power") == 0)
        {
            MQTT_SendSTAT("Power", SmartSwitch_RLY01_STATE ? "ON" : "OFF");
        }
        else if (strcmp(Message, "LED01") == 0)
        {
            MQTT_SendSTAT("LED01", SmartSwitch_LED01 ? "ON" : "OFF");
        }
        else if (strcmp(Message, "LNKLD") == 0)
        {
            MQTT_SendSTAT("LNKLD", SmartSwitch_LED02 ? "ON" : "OFF");
        }
        else if (strcmp(Message, "All") == 0)
        {
            MQTT_SendSTAT("Power", SmartSwitch_RLY01_STATE ? "ON" : "OFF");
            MQTT_SendSTAT("LED01", SmartSwitch_LED01 ? "ON" : "OFF");
            MQTT_SendSTAT("LNKLD", SmartSwitch_LED02 ? "ON" : "OFF");
        }
        // else if (strcmp(Message, "All") == 0)
    }

    else
    {
        DEBUG_Trouble("Dunno Whatcha want...");
        MQTT_SendNOTI("Error", "Dunno Whatcha want...");
    }
}
#endif
