#include <BfButton.h>
int SmartSwitch_ButtonPin[4];
int ButtonCount = 0;
#include "device_Buttons.h"

#include "Tinker_DEBUG.h"
extern char DEBUGtxt[92];

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

void Button_setup()
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

// // Handle button press
void ButtonPressHandler(BfButton *ButtonPin, BfButton::press_pattern_t pattern)
{
    String ButtonMessage = "Button on GPIO";
    ButtonMessage += ButtonPin->getID();

    switch (pattern)
    {
    case BfButton::SINGLE_PRESS:
        ButtonMessage += " single press";
        // Action: Toggle
        break;
    case BfButton::DOUBLE_PRESS:
        ButtonMessage += " double press";
        break;
    case BfButton::LONG_PRESS:
        ButtonMessage += " long press";
        break;
    }

    DEBUG_SectionTitle("SmartSwitch Action");
    DEBUG_LineOut(ButtonMessage.c_str());
}

void Button_init()
{

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

void Button_loop()
{
    Button0.read();
#ifdef SmartSwitch_BUTTN01
    Button1.read();
#endif
}
