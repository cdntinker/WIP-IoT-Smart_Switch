#include "Tinker_DEBUG.h"
extern char DEBUGtxt[92];
#include "MQTT.h" // emdedded functions for wifi and mqtt       should be cpp

#include "device_Buttons.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
// void MQTT_SendSTAT(const char *Topic, const char *Message);
//
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
#ifdef SmartSwitch_Bcount
#if (SmartSwitch_Bcount >= 1)
BfButton Button0(BfButton::STANDALONE_DIGITAL, GPIO_Button_PINS[0], true, LOW);
#endif
#if (SmartSwitch_Bcount >= 2)
BfButton Button1(BfButton::STANDALONE_DIGITAL, GPIO_Button_PINS[1], true, LOW);
#endif
#if (SmartSwitch_Bcount >= 3)
BfButton Button2(BfButton::STANDALONE_DIGITAL, GPIO_Button_PINS[2], true, LOW);
#endif
#if (SmartSwitch_Bcount >= 4)
BfButton Button3(BfButton::STANDALONE_DIGITAL, GPIO_Button_PINS[3], true, LOW);
#endif
#endif
//////////////////////////////////////////////////

// Handle button press
int ButtonNum;
void ButtonPressHandler(BfButton *ButtonPin, BfButton::press_pattern_t pattern)
{
    for (unsigned int i = 0; i < GPIO_Button_COUNT; i++) // Dig out the button number instead of GPIO
    {
        if (GPIO_Button_PINS[i] == ButtonPin->getID())
        {
            ButtonNum = i;
        }
    }

    String Topic = "button";
    Topic += (String)ButtonNum;

    String ButtonMessage;
    switch (pattern)
    {
    case BfButton::SINGLE_PRESS:
        ButtonMessage = "single press";
        // Action: Toggle
        break;
    case BfButton::DOUBLE_PRESS:
        ButtonMessage = "double press";
        break;
    case BfButton::LONG_PRESS:
        ButtonMessage = "long press";
        break;
    }

    String DEBUGmessage = Topic + " " + ButtonMessage;

    DEBUG_SectionTitle("SmartSwitch Action");
    DEBUG_LineOut(DEBUGmessage.c_str());

    // void MQTT_SendSTAT(const char *Topic, const char *Message);
    MQTT_SendTELE(Topic.c_str(), ButtonMessage.c_str());
}

void Button_setup()
{
    sprintf(DEBUGtxt, "Buttons: %2d", GPIO_Button_COUNT);
    DEBUG_LineOut(DEBUGtxt);
    strcpy(DEBUGtxt, "  GPIOs: ");
    for (unsigned int ctr = 0; ctr < GPIO_Button_COUNT; ctr++)
    {
        char BOOP[8];
        sprintf(BOOP, "%d=%d ", ctr, GPIO_Button_PINS[ctr]);
        strcat(DEBUGtxt, BOOP);
    }
    DEBUG_LineOut2(DEBUGtxt);

#ifdef SmartSwitch_Bcount
#if (SmartSwitch_Bcount >= 1)
    Button0.onPress(ButtonPressHandler)
        .onDoublePress(ButtonPressHandler)    // default timeout
        .onPressFor(ButtonPressHandler, 500); // custom timeout for 1/2 second
#endif
#if (SmartSwitch_Bcount >= 2)
    Button1.onPress(ButtonPressHandler)
        .onDoublePress(ButtonPressHandler)    // default timeout
        .onPressFor(ButtonPressHandler, 500); // custom timeout for 1/2 second
#endif
#if (SmartSwitch_Bcount >= 3)
    Button2.onPress(ButtonPressHandler)
        .onDoublePress(ButtonPressHandler)    // default timeout
        .onPressFor(ButtonPressHandler, 500); // custom timeout for 1/2 second
#endif
#if (SmartSwitch_Bcount >= 4)
    Button3.onPress(ButtonPressHandler)
        .onDoublePress(ButtonPressHandler)    // default timeout
        .onPressFor(ButtonPressHandler, 500); // custom timeout for 1/2 second
#endif
#endif
}

// // Turn Button on/off
// void Button_switch(int ButtonNum, bool OnOff)
// {
//     char MQTT_Topic[16];
//     sprintf(MQTT_Topic, "Button%02d", ButtonNum);
//     DEBUG_SectionTitle("SmartSwitch Action");
//     if (OnOff)
//     {
//         // DEBUG_LineOut("Button ON");
//         digitalWrite(GPIO_Button_PINS[ButtonNum], HIGH);
//         GPIO_Button_STATE[ButtonNum] = HIGH;
//         MQTT_SendSTAT(MQTT_Topic, "ON");
//         sprintf(DEBUGtxt, "Button %02d (%d) ON", ButtonNum, GPIO_Button_PINS[ButtonNum]);
//         DEBUG_LineOut(DEBUGtxt);
//     }
//     else
//     {
//         // DEBUG_LineOut("Button OFF");
//         digitalWrite(GPIO_Button_PINS[ButtonNum], LOW);
//         GPIO_Button_STATE[ButtonNum] = LOW;
//         MQTT_SendSTAT(MQTT_Topic, "OFF");
//         sprintf(DEBUGtxt, "Button %02d (%d) OFF", ButtonNum, GPIO_Button_PINS[ButtonNum]);
//         DEBUG_LineOut(DEBUGtxt);
//     }
// }
//
// // Turn relay on/off
// void Button_toggle(int ButtonNum)
// {
//     DEBUG_SectionTitle("SmartSwitch Action");
//     sprintf(DEBUGtxt, "Button %02d TOGGLE", ButtonNum);
//     DEBUG_LineOut(DEBUGtxt);
//     Button_switch(ButtonNum, !GPIO_Button_STATE[ButtonNum]);
// }
///////////////////////////////////////////////////////////////////////////////////////////

void Button_loop()
{

#ifdef SmartSwitch_Bcount
#if (SmartSwitch_Bcount >= 1)
    Button0.read();
#endif
#if (SmartSwitch_Bcount >= 2)
    Button1.read();
#endif
#if (SmartSwitch_Bcount >= 3)
    Button2.read();
#endif
#if (SmartSwitch_Bcount >= 4)
    Button3.read();
#endif
#endif
}
