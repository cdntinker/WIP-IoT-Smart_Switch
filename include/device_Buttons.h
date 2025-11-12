
#include <BfButton.h>

// extern int SmartSwitch_ButtonPin[4];
// extern unsigned int GPIO_Button_PINS[4];
// extern bool GPIO_Button_STATE[10];
extern unsigned int GPIO_Button_COUNT;

// extern int ButtonCount;

void Button_setup();
void ButtonPressHandler(BfButton *ButtonPin, BfButton::press_pattern_t pattern);

// void Button_init();

// void ButtonPressHandler(BfButton *ButtonPin, BfButton::press_pattern_t pattern);
