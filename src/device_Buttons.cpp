#include "Tinker_DEBUG.h"
extern char DEBUGtxt[92];

void MQTT_SendSTAT(const char *Topic, const char *Message);

//////////////////////////////////////////////////
#define GPIO_Buttons(...) unsigned int GPIO_Button_PINS[] = {__VA_ARGS__}
#ifdef SmartSwitch_Buttons
GPIO_Buttons(SmartSwitch_Buttons);
unsigned int GPIO_Button_COUNT = sizeof(GPIO_Button_PINS) / sizeof(GPIO_Button_PINS[0]);
#else
unsigned int GPIO_Button_PINS[] = {0};
unsigned int GPIO_Button_COUNT = 0;
#endif
bool GPIO_Button_STATE[10]; // 10 is arbitrary...
//////////////////////////////////////////////////
 
void Button_setup()
{
    for (unsigned int CTR = 0; CTR < GPIO_Button_COUNT; CTR++)
    {
        pinMode(GPIO_Button_PINS[CTR], INPUT);
    }
}

// Turn Button on/off
void Button_switch(int ButtonNum, bool OnOff)
{
    char MQTT_Topic[16];
    sprintf(MQTT_Topic, "Button%02d", ButtonNum);
    DEBUG_SectionTitle("SmartSwitch Action");
    if (OnOff)
    {
        // DEBUG_LineOut("Button ON");
        digitalWrite(GPIO_Button_PINS[ButtonNum], HIGH);
        GPIO_Button_STATE[ButtonNum] = HIGH;
        MQTT_SendSTAT(MQTT_Topic, "ON");
        sprintf(DEBUGtxt, "Button %02d (%d) ON", ButtonNum, GPIO_Button_PINS[ButtonNum]);
        DEBUG_LineOut(DEBUGtxt);
    }
    else
    {
        // DEBUG_LineOut("Button OFF");
        digitalWrite(GPIO_Button_PINS[ButtonNum], LOW);
        GPIO_Button_STATE[ButtonNum] = LOW;
        MQTT_SendSTAT(MQTT_Topic, "OFF");
        sprintf(DEBUGtxt, "Button %02d (%d) OFF", ButtonNum, GPIO_Button_PINS[ButtonNum]);
        DEBUG_LineOut(DEBUGtxt);
    }
}

// Turn relay on/off
void Button_toggle(int ButtonNum)
{
    DEBUG_SectionTitle("SmartSwitch Action");
    sprintf(DEBUGtxt, "Button %02d TOGGLE", ButtonNum);
    DEBUG_LineOut(DEBUGtxt);
    Button_switch(ButtonNum, !GPIO_Button_STATE[ButtonNum]);
}
