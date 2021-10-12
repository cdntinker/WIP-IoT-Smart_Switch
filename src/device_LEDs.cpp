#include "Tinker_DEBUG.h"
extern char DEBUGtxt[92];

void MQTT_SendSTAT(const char *Topic, const char *Message);

int SmartSwitch_LEDPin[4];
bool SmartSwitch_LED_STATE[4];
int LEDCount = 0;

void LED_setup()
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
// Turn LED on/off
void LED_switch(int LEDNum, bool OnOff)
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
void LED_toggle(int LEDNum)
{
    DEBUG_SectionTitle("SmartSwitch Action");
    sprintf(DEBUGtxt, "LED %02d TOGGLE", LEDNum);
    DEBUG_LineOut(DEBUGtxt);
    LED_switch(LEDNum, !SmartSwitch_LED_STATE[LEDNum]);
}
