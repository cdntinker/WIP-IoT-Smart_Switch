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

// #include <Tinker_SmartSwitch.h>
#include "Tinker_SmartSwitch.h"     //  Building with embeded version in Arduino prefers quotes
#include "device_Relays.h"
#include "device_LEDs.h"

#ifndef DEVICE_Translations
#define DEVICE_Translations


extern int SmartSwitch_RelayPin[4];
extern bool SmartSwitch_Relay_STATE[4];

extern int SmartSwitch_LEDPin[4];
extern bool SmartSwitch_LED_STATE[4];

extern int SmartSwitch_ButtonPin[4];


#define DEVICE_SETUP SmartSwitch_init
#define DEVICE_LOOP Button_loop

void DEVICE_SETUP();
void DEVICE_LOOP();

#define DEVICE_RELAY Relay_switch
#define DEVICE_TOGGLE Relay_toggle

#define DEVICE_LED LED_switch
#define DEVICE_LED_TOGGLE LED_toggle

#define DEVICE_MQTT_IN SmartSwitch_MQTT_in

#endif // DEVICE_Translations

/////////////////////////////////////////////////////////////

