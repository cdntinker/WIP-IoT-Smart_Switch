#ifndef config_h
#define config_h

#include "Arduino.h"

/* ----------------- General config -------------------------------- */

/* Varibles here are filled in by the config system */
char        host[32];
char        group[32] = "AustinOTAs";
char        ssid[32];
char        password[64];

char        AP_SSID[32];
char        AP_PASS[64];
uint8_t     AP_CHANNEL  = 1; // not written over
uint8_t     AP_HIDDEN;
uint8_t     AP_MAX_CON  = 1; // not written over

char        mqtt_broker[32];
uint16_t    mqtt_port;
char        mqtt_username[32];
char        mqtt_password[32];

uint8_t     darkState;
char        htmltitle[32];
char        htmltype[32];
char        htmlcolor[10];
char        htmlhover[10];

uint8_t     brightness;            // set strip brightness

const char *DeviceNotes PROGMEM = R"rawliteral(
# Welcome to IdIoT.                                                                             #
# Yet another bit of code by austinscreations that I'm mutilating into submission...                #)rawliteral";

#endif
