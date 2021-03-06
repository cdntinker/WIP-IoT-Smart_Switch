#include <BfButton.h>
int SmartSwitch_ButtonPin[4];
int ButtonCount = 0;
#include "device_Buttons.h"

#include "Tinker_DEBUG.h"
extern char DEBUGtxt[92];

//////////////////////////////////////////////////
// #define GPIO_Buttons(...) unsigned int GPIO_Button_PINS[] = {__VA_ARGS__}
// #ifdef SmartSwitch_Buttons
// GPIO_Buttons(SmartSwitch_Buttons);
// unsigned int GPIO_Button_COUNT = sizeof(GPIO_Button_PINS) / sizeof(GPIO_Button_PINS[0]);
// #else
// unsigned int GPIO_Button_PINS[] = {0};
// unsigned int GPIO_Button_COUNT = 0;
// #endif
// bool GPIO_Button_STATE[10]; // 10 is arbitrary...
//////////////////////////////////////////////////


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

// void Button_setup()
//     {
//     // for (unsigned int CTR = 0; CTR < GPIO_Button_COUNT; CTR++)
//     //     pinMode(GPIO_Button_PINS[CTR], INPUT);
// #ifdef SmartSwitch_BUTTN00
//         SmartSwitch_ButtonPin[ButtonCount] = SmartSwitch_BUTTN00;
//         pinMode(SmartSwitch_ButtonPin[ButtonCount], INPUT_PULLUP);
//         ButtonCount++;
// #endif
// #ifdef SmartSwitch_BUTTN01
//         SmartSwitch_ButtonPin[ButtonCount] = SmartSwitch_BUTTN01;
//         pinMode(SmartSwitch_ButtonPin[ButtonCount], INPUT);
//         ButtonCount++;
// #endif
// #ifdef SmartSwitch_BUTTN02
//         SmartSwitch_ButtonPin[ButtonCount] = SmartSwitch_BUTTN02;
//         pinMode(SmartSwitch_ButtonPin[ButtonCount], INPUT);
//         ButtonCount++;
// #endif
// #ifdef SmartSwitch_BUTTN03
//         SmartSwitch_ButtonPin[ButtonCount] = SmartSwitch_BUTTN03;
//         pinMode(SmartSwitch_ButtonPin[ButtonCount], INPUT);
//         ButtonCount++;
// #endif
//     }
// void MQTT_SendTELE(const char *Topic, const char *Message);

// // Handle button press
void ButtonPressHandler(BfButton *ButtonPin, BfButton::press_pattern_t pattern)
{
//     String ButtonMessage = "GPIObutton";
//     ButtonMessage += ButtonPin->getID();
// String Topic = ButtonMessage;

//     switch (pattern)
//     {
//     case BfButton::SINGLE_PRESS:
//         ButtonMessage = "single press";
//         // Action: Toggle
//         break;
//     case BfButton::DOUBLE_PRESS:
//         ButtonMessage = "double press";
//         break;
//     case BfButton::LONG_PRESS:
//         ButtonMessage = "long press";
//         break;
//     }

// String DEBUGmessage = Topic + " " + ButtonMessage;

//     DEBUG_SectionTitle("SmartSwitch Action");
//     DEBUG_LineOut(DEBUGmessage.c_str());

// // void MQTT_SendSTAT(const char *Topic, const char *Message);
//  MQTT_SendTELE(Topic.c_str(), ButtonMessage.c_str());
}

void Button_init()
{

    //////////////////////
#ifdef SmartSwitch_BUTTN00
    Button0.onPress(ButtonPressHandler)
        .onDoublePress(ButtonPressHandler)    // default timeout
        .onPressFor(ButtonPressHandler, 500); // custom timeout for 1/2 second
#endif
    //////////////////////
#ifdef SmartSwitch_BUTTN01
    Button1.onPress(ButtonPressHandler)
        .onDoublePress(ButtonPressHandler)    // default timeout
        .onPressFor(ButtonPressHandler, 500); // custom timeout for 1/2 second
#endif
    //////////////////////
}

void Button_loop()
{
#ifdef SmartSwitch_BUTTN00
    Button0.read();
#endif
#ifdef SmartSwitch_BUTTN01
    Button1.read();
#endif
}
