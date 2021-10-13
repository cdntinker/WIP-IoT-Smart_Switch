#include "Tinker_DEBUG.h"
extern char DEBUGtxt[92];

void MQTT_SendSTAT(const char *Topic, const char *Message);

//////////////////////////////////////////////////
#define GPIO_LEDs(...) unsigned int GPIO_LED_PINS[] = {__VA_ARGS__}
#ifdef SmartSwitch_LEDs
GPIO_LEDs(SmartSwitch_LEDs);
unsigned int GPIO_LED_COUNT = sizeof(GPIO_LED_PINS) / sizeof(GPIO_LED_PINS[0]);
#else
unsigned int GPIO_LED_PINS[] = {0};
unsigned int GPIO_LED_COUNT = 0;
#endif
bool GPIO_LED_STATE[10]; // 10 is arbitrary...
//////////////////////////////////////////////////

void LED_setup()
{
    for (unsigned int CTR = 0; CTR < GPIO_LED_COUNT; CTR++)
        pinMode(GPIO_LED_PINS[CTR], OUTPUT);
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
        digitalWrite(GPIO_LED_PINS[LEDNum], HIGH);
        GPIO_LED_STATE[LEDNum] = HIGH;
        MQTT_SendSTAT(MQTT_Topic, "ON");
        sprintf(DEBUGtxt, "LED %02d (%d) ON", LEDNum, GPIO_LED_PINS[LEDNum]);
        DEBUG_LineOut(DEBUGtxt);
    }
    else
    {
        // DEBUG_LineOut("LED OFF");
        digitalWrite(GPIO_LED_PINS[LEDNum], LOW);
        GPIO_LED_STATE[LEDNum] = LOW;
        MQTT_SendSTAT(MQTT_Topic, "OFF");
        sprintf(DEBUGtxt, "LED %02d (%d) OFF", LEDNum, GPIO_LED_PINS[LEDNum]);
        DEBUG_LineOut(DEBUGtxt);
    }
}

// Turn relay on/off
void LED_toggle(int LEDNum)
{
    DEBUG_SectionTitle("SmartSwitch Action");
    sprintf(DEBUGtxt, "LED %02d TOGGLE", LEDNum);
    DEBUG_LineOut(DEBUGtxt);
    LED_switch(LEDNum, !GPIO_LED_STATE[LEDNum]);
}
