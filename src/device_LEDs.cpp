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
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // This should probably be handled based on a build_flag in pio_Modules.ini
    unsigned int LED_ON;
    unsigned int LED_OFF;
    char LED_STATE[4] = "-";
    if ((strcmp(STR(DeviceType), "D1-Mini") == 0) 
        || (strcmp(STR(BoardType), "Sonoff_Basic") == 0) 
        || (strcmp(STR(BoardType), "ESP-M3b") == 0)
       )
    { // Devices with Active-Low LEDs
        LED_ON = LOW;
        LED_OFF = HIGH;
    }
    else
    { // Devices with Active-High LEDs
        LED_ON = HIGH;
        LED_OFF = LOW;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (OnOff)
    {
        digitalWrite(GPIO_LED_PINS[LEDNum], LED_ON);
        GPIO_LED_STATE[LEDNum] = HIGH;
        strcpy(LED_STATE, "ON");
    }
    else
    {
        digitalWrite(GPIO_LED_PINS[LEDNum], LED_OFF);
        GPIO_LED_STATE[LEDNum] = LOW;
        strcpy(LED_STATE, "OFF");
    }

    MQTT_SendSTAT(MQTT_Topic, LED_STATE);
    sprintf(DEBUGtxt, "LED %02d (%d) %s", LEDNum, GPIO_LED_PINS[LEDNum], LED_STATE);
    DEBUG_LineOut(DEBUGtxt);
    /***********************************************
     * TODO: update the UI to reflect these actions
     ***********************************************/
}

// Turn LED on/off
void LED_toggle(int LEDNum)
{
    DEBUG_SectionTitle("SmartSwitch Action");
    sprintf(DEBUGtxt, "LED %02d TOGGLE", LEDNum);
    DEBUG_LineOut(DEBUGtxt);
    LED_switch(LEDNum, !GPIO_LED_STATE[LEDNum]);
}
