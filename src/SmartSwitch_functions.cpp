#include <Arduino.h>

#include "Tinker_SmartSwitch.h"
// #include "Tinker_MQTT.h"
#define MQTT_BUFFER_SIZE (100) // This number is arbitrary

void MQTT_SendSTAT(const char *Topic, const char *Message);
void MQTT_SendNOTI(const char *Topic, const char *Message);
void MQTT_SendTELE(const char *Topic, const char *Message);

#include "Tinker_DEBUG.h"
extern char DEBUGtxt[92];

int SmartSwitch_RelayPin[4];
bool SmartSwitch_Relay_STATE[4];
int RelayCount = 0;

int SmartSwitch_LEDPin[4];
bool SmartSwitch_LED_STATE[4];
int LEDCount = 0;

#include <BfButton.h>

int SmartSwitch_ButtonPin[4];

int ButtonCount = 0;

// const unsigned int btnPin = SmartSwitch_BUTTN00;
#ifdef SmartSwitch_BUTTN00
BfButton Button0(BfButton::STANDALONE_DIGITAL, SmartSwitch_BUTTN00, false, LOW);
#endif
#ifdef SmartSwitch_BUTTN01
BfButton Button1(BfButton::STANDALONE_DIGITAL, SmartSwitch_BUTTN01, false, LOW);
#endif
#ifdef SmartSwitch_BUTTN02
BfButton Button2(BfButton::STANDALONE_DIGITAL, SmartSwitch_BUTTN02, false, LOW);
#endif
#ifdef SmartSwitch_BUTTN03
BfButton Button3(BfButton::STANDALONE_DIGITAL, SmartSwitch_BUTTN03, false, LOW);
#endif

void ButtonPressHandler(BfButton *ButtonPin, BfButton::press_pattern_t pattern);

void SmartSwitch_init()
{
    DEBUG_Init("SmartSwitch");

/*****  Relays  *****/
{
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
}

/*****  Buttons  *****/
{
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
}

/*****  LEDs  *****/
{
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
}

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

    //////////////////////
    Button0.onPress(ButtonPressHandler)
        .onDoublePress(ButtonPressHandler)    // default timeout
        .onPressFor(ButtonPressHandler, 500); // custom timeout for 1/2 second
    //////////////////////
#ifdef SmartSwitch_BUTTN01
    Button1.onPress(ButtonPressHandler)
        .onDoublePress(ButtonPressHandler)    // default timeout
        .onPressFor(ButtonPressHandler, 500); // custom timeout for 1/2 second
#endif
    //////////////////////
}

void SmartSwitch_loop()
{
    Button0.read();
#ifdef SmartSwitch_BUTTN01
    Button1.read();
#endif
}

// // Handle button press
void ButtonPressHandler(BfButton *ButtonPin, BfButton::press_pattern_t pattern)
{
    String ButtonMessage = "Button ";
    ButtonMessage += ButtonPin->getID();

    switch (pattern)
    {
    case BfButton::SINGLE_PRESS:
        ButtonMessage += " pressed.";
        // Action: Toggle
        break;
    case BfButton::DOUBLE_PRESS:
        ButtonMessage += " double pressed.";
        break;
    case BfButton::LONG_PRESS:
        ButtonMessage += " long pressed.";
        break;
    }

    DEBUG_SectionTitle("SmartSwitch Action");
    DEBUG_LineOut(ButtonMessage.c_str());
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
    DEBUG_SectionTitle("SmartSwitch Action");
    if (OnOff)
    {
        // DEBUG_LineOut("LED ON");
        digitalWrite(SmartSwitch_LEDPin[LEDNum], HIGH);
        SmartSwitch_LED_STATE[LEDNum] = HIGH;
        MQTT_SendSTAT(MQTT_Topic, "ON");
        sprintf(DEBUGtxt, "LED %02d (%d) ON", LEDNum, SmartSwitch_LEDPin[LEDNum]);
        DEBUG_LineOut(DEBUGtxt);
    }
    else
    {
        // DEBUG_LineOut("LED OFF");
        digitalWrite(SmartSwitch_LEDPin[LEDNum], LOW);
        SmartSwitch_LED_STATE[LEDNum] = LOW;
        MQTT_SendSTAT(MQTT_Topic, "OFF");
        sprintf(DEBUGtxt, "LED %02d (%d) OFF", LEDNum, SmartSwitch_LEDPin[LEDNum]);
        DEBUG_LineOut(DEBUGtxt);
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

// Handle incoming MQTT messages for the SmartSwitch functionality
#define DEVICE_RELAY SmartSwitch_Relay
#define DEVICE_TOGGLE SmartSwitch_Toggle
#define DEVICE_LED SmartSwitch_LED
#define DEVICE_LED_TOGGLE SmartSwitch_LED_Toggle

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
            CTRfinish = RelayCount;
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
            if (TheTopic.toInt() < RelayCount)
            {
                if (strcmp(MQTT_msg_in, "on") == 0)
                    DEVICE_RELAY(CTR, HIGH);
                if (strcmp(MQTT_msg_in, "off") == 0)
                    DEVICE_RELAY(CTR, LOW);
                if (strcmp(MQTT_msg_in, "toggle") == 0)
                    DEVICE_TOGGLE(CTR);
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
            CTRfinish = LEDCount;
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
            if (TheTopic.toInt() < LEDCount)
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
            MQTT_SendSTAT("Power", SmartSwitch_Relay_STATE[0] ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "LED01") == 0)
        {
            MQTT_SendSTAT("LED01", SmartSwitch_LED_STATE[0] ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "LNKLD") == 0)
        {
            MQTT_SendSTAT("LNKLD", SmartSwitch_LED_STATE[1] ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "All") == 0)
        {
            MQTT_SendSTAT("Power", SmartSwitch_Relay_STATE[0] ? "ON" : "OFF");
            MQTT_SendSTAT("LED01", SmartSwitch_LED_STATE[0] ? "ON" : "OFF");
            MQTT_SendSTAT("LNKLD", SmartSwitch_LED_STATE[1] ? "ON" : "OFF");
        }
        // else if (strcmp(MQTT_msg_in, "All") == 0)
    }

    else // Ya cornfoozed me!
    {
        DEBUG_Trouble("Dunno Whatcha want...");
        MQTT_SendNOTI("Error", "Dunno Whatcha want...");
    }
}
