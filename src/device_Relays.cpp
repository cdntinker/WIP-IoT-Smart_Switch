#include "Tinker_DEBUG.h"
extern char DEBUGtxt[92];

void MQTT_SendSTAT(const char *Topic, const char *Message);

int SmartSwitch_RelayPin[4];
bool SmartSwitch_Relay_STATE[4];
int RelayCount = 0;

String SmartSwitch_TurnOn;
String SmartSwitch_TurnOff;

void Relay_setup()
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

// Turn relay on/off
void Relay_switch(int RelayNum, bool OnOff)
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
void Relay_toggle(int RelayNum)
{
    DEBUG_SectionTitle("SmartSwitch Action");
    sprintf(DEBUGtxt, "Relay %02d TOGGLE", RelayNum);
    DEBUG_LineOut(DEBUGtxt);
    Relay_switch(RelayNum, !SmartSwitch_Relay_STATE[RelayNum]);
}
