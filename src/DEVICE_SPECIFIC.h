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

#include <Tinker_SiniLink.h>

#ifndef DEVICE_Translations
#define DEVICE_Translations

extern bool SiniLink_PWR_STATE;
extern bool SiniLink_LED01_STATE;
extern bool SiniLink_LED02_STATE;

#define DEVICE_SETUP SiniLink_init
#define DEVICE_LOOP NULL_function

void DEVICE_SETUP();
void DEVICE_LOOP();

#define DEVICE_RELAY SiniLink_Relay
#define DEVICE_TOGGLE SiniLink_Toggle

#endif // DEVICE_Translations

/////////////////////////////////////////////////////////////

