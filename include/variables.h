/*
 * varibles used by main program
 * 
 * shouldn't need to be edited
 */

#ifndef varibles_h
#define varibles_h

#include <Arduino.h>

/* General */
bool            restartRequired = false;        // have we told the device to restart?
bool            factoryRequired = false;        // have we told the device to factory reset?

const char*     PARAM_ID = "ID";                // used for wifi button
unsigned long   timeout;                        // used to ensure we don't get an indefinetly hold from wifi button
uint8_t         WIFIbuttonSTATE[4] = {1,1,1,1};

unsigned long   lastDelete = 0;                 // gives time for factory reset to change url then delete data and reboot

unsigned long   lastUpdate;                     // used to keep track of updates to webpage with websocket json
uint8_t         ws_connected;                   // keep track of the number of clients connected

float           new_sat;                        // used by ESP_color for calculating the Saturation Level
uint8_t         white_reverse;                  // used for flipping the white LED level for calculating the new Saturation level

uint8_t         neo_update[5]    = {false};     // do led's need to be updated - prevents flickering from constant updates
uint8_t         neo_override[5]  = {false};     // do led's need to be updated - prevents flickering from constant updates -- used in overrideMODE
unsigned long   lastdouble;                     // used for double flash animation
uint8_t         doubletime;                     // used for double flash animation
uint8_t         ledState         = LOW;         // ledState used to set the LED flash
uint8_t         connected_update = false;       // update leds to show connection progress
uint8_t         ringspeed        = 250;         // speed in millis() for ring animation in voltage lockout
uint8_t         flashState[5]    = {LOW};       // array of current flash state -- helps with ensureing neopixel updates without spamming neopixel line causing flickering
uint8_t         prevflash[5]     = {LOW};       // array of last flash state    -- helps with ensureing neopixel updates without spamming neopixel line causing flickering
uint8_t         ledmode[5]       = {0};         // what mode the leds are in    -- used in overrideMODE control

/* mqtt topics */
const char*     out_heart  = "-";               // LWT topic

char            MQTT_heartbeat[60];

String          IPaddress;                      // IP address for 'outTopic'

/* mqtt config input */
uint8_t         mqttC;                          // what port to change
uint16_t        mqttCur;                        // current that a port is being set to
String          mqttState;                      // state that a port is being set to
uint8_t         rednew[5] = {0};                // new LED color for override MODE     -- RED
uint8_t         grnnew[5] = {0};                // new LED color for override MODE     -- GREEN
uint8_t         blunew[5] = {0};                // new LED color for override MODE     -- BLUE
uint8_t         whinew[5] = {0};                // new LED color for override MODE     -- WHITE
 
 #endif
