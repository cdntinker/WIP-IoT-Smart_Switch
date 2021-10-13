#include "Tinker_DEBUG.h"
extern char DEBUGtxt[92];

void MQTT_SendSTAT(const char *Topic, const char *Message);

String SmartSwitch_TurnOn;
String SmartSwitch_TurnOff;

// //////////////////////////////////////////////////
#define GPIO_Relays(...) unsigned int GPIO_Relay_PINS[] = {__VA_ARGS__}
#ifdef SmartSwitch_Relays
GPIO_Relays(SmartSwitch_Relays);
unsigned int GPIO_Relay_COUNT = sizeof(GPIO_Relay_PINS) / sizeof(GPIO_Relay_PINS[0]);
#else
unsigned int GPIO_Relay_PINS[] = {0};
unsigned int GPIO_Relay_COUNT = 0;
#endif
bool GPIO_Relay_STATE[10]; // 10 is arbitrary...
// //////////////////////////////////////////////////

void Relay_setup()
{
    for (unsigned int CTR = 0; CTR < GPIO_Relay_COUNT; CTR++)
        pinMode(GPIO_Relay_PINS[CTR], OUTPUT);
}

// Turn relay on/off
void Relay_switch(int RelayNum, bool OnOff)
{
    char MQTT_Topic[16];
    sprintf(MQTT_Topic, "Power%02d", RelayNum);
    DEBUG_SectionTitle("SmartSwitch Action");
    if (OnOff)
    {
        digitalWrite(GPIO_Relay_PINS[RelayNum], HIGH);
        GPIO_Relay_STATE[RelayNum] = HIGH;
        SmartSwitch_TurnOn = "ButtonHere";
        SmartSwitch_TurnOff = "ButtonClickable";
        MQTT_SendSTAT(MQTT_Topic, "ON");
        sprintf(DEBUGtxt, "Relay %02d (%d) ON", RelayNum, GPIO_Relay_PINS[RelayNum]);
        DEBUG_LineOut(DEBUGtxt);
    }
    else
    {
        digitalWrite(GPIO_Relay_PINS[RelayNum], LOW);
        GPIO_Relay_STATE[RelayNum] = LOW;
        SmartSwitch_TurnOn = "ButtonClickable";
        SmartSwitch_TurnOff = "ButtonHere";
        MQTT_SendSTAT(MQTT_Topic, "OFF");
        sprintf(DEBUGtxt, "Relay %02d (%d) OFF", RelayNum, GPIO_Relay_PINS[RelayNum]);
        DEBUG_LineOut(DEBUGtxt);
    }
}

// Turn relay on/off
void Relay_toggle(int RelayNum)
{
    DEBUG_SectionTitle("SmartSwitch Action");
    sprintf(DEBUGtxt, "Relay %02d TOGGLE", RelayNum);
    DEBUG_LineOut(DEBUGtxt);
    Relay_switch(RelayNum, !GPIO_Relay_STATE[RelayNum]);
}
