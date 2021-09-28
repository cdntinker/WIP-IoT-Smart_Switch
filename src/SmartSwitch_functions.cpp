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
    pinMode(SmartSwitch_RelayPin[LEDCount], OUTPUT);
    RelayCount++;
#endif
#ifdef SmartSwitch_RELAY01
    SmartSwitch_RelayPin[RelayCount] = SmartSwitch_RELAY01;
    pinMode(SmartSwitch_RelayPin[LEDCount], OUTPUT);
    RelayCount++;
#endif
#ifdef SmartSwitch_RELAY02
    SmartSwitch_RelayPin[RelayCount] = SmartSwitch_RELAY02;
    pinMode(SmartSwitch_RelayPin[LEDCount], OUTPUT);
    RelayCount++;
#endif
#ifdef SmartSwitch_RELAY03
    SmartSwitch_RelayPin[RelayCount] = SmartSwitch_RELAY03;
    pinMode(SmartSwitch_RelayPin[LEDCount], OUTPUT);
    RelayCount++;
#endif

/*****  Buttons  *****/
#ifdef SmartSwitch_BUTTN00
    SmartSwitch_ButtonPin[ButtonCount] = SmartSwitch_BUTTN00;
    pinMode(SmartSwitch_ButtonPin[LEDCount], INPUT);
    ButtonCount++;
#endif
#ifdef SmartSwitch_BUTTN01
    SmartSwitch_ButtonPin[ButtonCount] = SmartSwitch_BUTTN01;
    pinMode(SmartSwitch_ButtonPin[LEDCount], INPUT);
    ButtonCount++;
#endif
#ifdef SmartSwitch_BUTTN02
    SmartSwitch_ButtonPin[ButtonCount] = SmartSwitch_BUTTN02;
    pinMode(SmartSwitch_ButtonPin[LEDCount], INPUT);
    ButtonCount++;
#endif
#ifdef SmartSwitch_BUTTN03
    SmartSwitch_ButtonPin[ButtonCount] = SmartSwitch_BUTTN03;
    pinMode(SmartSwitch_ButtonPin[LEDCount], INPUT);
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

    Serial.printf("Relays: %2d ( ", RelayCount);
    for (int ctr = 0; ctr < RelayCount; ctr++)
    {
        Serial.printf("%2d ", SmartSwitch_RelayPin[ctr]);
    }
    Serial.println(")");

    Serial.printf("Relays: %2d ( ", ButtonCount);
    for (int ctr = 0; ctr < ButtonCount; ctr++)
    {
        Serial.printf("%2d ", SmartSwitch_ButtonPin[ctr]);
    }
    Serial.println(")");

    Serial.printf("  LEDs: %2d ( ", LEDCount);
    for (int ctr = 0; ctr < LEDCount; ctr++)
    {
        Serial.printf("%2d ", SmartSwitch_LEDPin[ctr]);
    }
    Serial.println(")");
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
    DEBUG_SectionTitle("SmartSwitch Action");
    if (OnOff)
    {
        digitalWrite(SmartSwitch_RelayPin[RelayNum], HIGH);
        SmartSwitch_Relay_STATE[RelayNum] = HIGH;
        SmartSwitch_TurnOn = "ButtonHere";
        SmartSwitch_TurnOff = "ButtonClickable";
        MQTT_SendSTAT("Power", "ON");
        sprintf(DEBUGtxt, "Relay %02d ON", RelayNum);
        DEBUG_LineOut(DEBUGtxt);
    }
    else
    {
        digitalWrite(SmartSwitch_RelayPin[RelayNum], LOW);
        SmartSwitch_Relay_STATE[RelayNum] = LOW;
        SmartSwitch_TurnOn = "ButtonClickable";
        SmartSwitch_TurnOff = "ButtonHere";
        MQTT_SendSTAT("Power", "OFF");
        sprintf(DEBUGtxt, "Relay %02d OFF", RelayNum);
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
    if (OnOff)
    {
        DEBUG_LineOut("LED ON");
        digitalWrite(SmartSwitch_LED01, HIGH);
        SmartSwitch_LED_STATE[LEDNum] = HIGH;
        MQTT_SendSTAT("LED01", "ON");
    }
    else
    {
        DEBUG_LineOut("LED OFF");
        digitalWrite(SmartSwitch_LED01, LOW);
        SmartSwitch_LED_STATE[LEDNum] = LOW;
        MQTT_SendSTAT("LED01", "OFF");
    }
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
