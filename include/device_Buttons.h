
#include <BfButton.h>

extern int SmartSwitch_ButtonPin[4];

extern int ButtonCount;

void Button_init();

void ButtonPressHandler(BfButton *ButtonPin, BfButton::press_pattern_t pattern);
