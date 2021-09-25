/////////////////////////////////////////////////////////////
//  Here's a kinda cool thing...
//
//  #defineing DEVICE_SETUP & DEVICE_LOOP like this means you
//  no longer need to edit the setup() & loop() functions to
//  customize this code for individual devices. :)
//
//  Now...
//  If I can find a way to build the actual function names
//  from DeviceName...
//  That'd be bloody cool.
/////////////////////////////////////////////////////////////

#include <Tinker_SmartSwitch.h>

#ifndef DEVICE_Translations
#define DEVICE_Translations

extern bool SmartSwitch_PWR_STATE;
extern bool SmartSwitch_LED01_STATE;
extern bool SmartSwitch_LED02_STATE;

#define DEVICE_SETUP SmartSwitch_init
#define DEVICE_LOOP NULL_function

void DEVICE_SETUP();
void DEVICE_LOOP();

#define DEVICE_RELAY SmartSwitch_Relay
#define DEVICE_TOGGLE SmartSwitch_Toggle

#define DEVICE_LED01 SmartSwitch_LED
#define DEVICE_LED02 SmartSwitch_LINKLED

#endif // DEVICE_Translations

/////////////////////////////////////////////////////////////

