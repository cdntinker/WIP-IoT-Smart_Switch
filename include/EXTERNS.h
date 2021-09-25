/*
 * varibles used by main program
 * 
 * shouldn't need to be edited
 */

#include <Arduino.h>
 
 //////////////////////////////////////
 // From varibles.h
 //////////////////////////////////////

/* General */
extern bool restartRequired;            // have we told the device to restart?
extern bool factoryRequired;            // have we told the device to factory reset?

extern const char PARAM_ID[];           // used for wifi button
extern unsigned long timeout;           // used to ensure we don't get an indefinetly hold from wifi button
extern uint8_t WIFIbuttonSTATE[4];

extern unsigned long lastDelete;        // gives time for factory reset to change url then delete data and reboot

extern unsigned long lastUpdate;        // used to keep track of updates to webpage with websocket json
extern uint8_t ws_connected;            // keep track of the number of clients connected

extern float new_sat;                   // used by ESP_color for calculating the Saturation Level
extern uint8_t white_reverse;           // used for flipping the white LED level for calculating the new Saturation level

/* Buttons */
// extern int buttons[5];        // pin button is connected to

/* MCP Pinout */
// extern uint8_t mcp_update[5];       // used to limit constant updates
// extern uint8_t MCP_en[5];     // pin power fets connected on mcp
// extern uint8_t MCP_data[5];     // pin data  fets connected on mcp

/* LED's */
// #define LED_PIN                0                    // pin neopixels are connected to -- shouldn't need to be changed
// #define LED_COUNT              4                    // number of neopixels
// #define LED_TYPE               NEO_GRBW             // type of led's used
extern uint8_t neo_update[5];               // do led's need to be updated - prevents flickering from constant updates
extern uint8_t neo_override[5];             // do led's need to be updated - prevents flickering from constant updates -- used in overrideMODE
extern unsigned long lastdouble;            // used for double flash animation
extern uint8_t       doubletime;            // used for double flash animation
extern uint8_t       ledState;              // ledState used to set the LED flash
extern uint8_t       connected_update;      // update leds to show connection progress
extern uint8_t       ringspeed;             // speed in millis() for ring animation in voltage lockout
extern uint8_t       flashState[5];         // array of current flash state -- helps with ensureing neopixel updates without spamming neopixel line causing flickering
extern uint8_t       prevflash[5];          // array of last flash state    -- helps with ensureing neopixel updates without spamming neopixel line causing flickering
extern uint8_t       ledmode[5];            // what mode the leds are in    -- used in overrideMODE control

/* varibles */
// extern  uint8_t port_state[5]; //sets the state of the port 0 off, 1 power, 2 data+power
// extern  uint8_t last_press[5]; // stores the last press if a button for the sketch to process, then reset (15 = hold)
// extern  uint8_t port_INA[5]; // state of an INA on a port - if failed to load it disables the port

/* voltage varibles */
// extern float         busvoltage;      // average voltage from all 4 sensors
// extern unsigned long lastvoltread;        // last voltage reading
// extern unsigned long lastvoltmqtt;        // last time the voltage was sent via mqtt
// extern uint8_t       voltlockout;         // voltage lockout - 0 = off / safe 1 = under volt 2 = over volt
// extern uint8_t       voltlockout_prev;    // last volatge lockout varible - for reseting led's
// extern uint8_t       fwd;                 // led aniamtion
// extern uint8_t       fwd_prev;            // led aniamtion prev value
// extern unsigned long prevringMillis;  // speed of animation

/* current measurement varibles */
// extern uint16_t       CALCmaxtotal; // how much power used by all ports
// extern int            currentValue[5]; // initialization of current measurement
// extern int            wattsValue[5]; // initialization of current measurement
// extern int            EMA_C[5]; // initialization of EMA C  - filtered current measurement
// extern int            EMA_W[5]; // initialization of EMA C  - filtered current measurement
// extern float          EMA_a; // initialization of EMA alpha
// extern unsigned long  lastINAread[5]; // last time the current was read
// extern unsigned long  lastINAmqtt[5]; // last time the current was sent via mqtt

/* mqtt topics */
extern const char* out_heart;  // LWT        topic

extern const char* out_topic1; // button     topic
extern const char* out_topic2;  // port       topic
extern const char* out_topic3;  // volt       topic

extern const char* in_topic1;   // current    topic
extern const char* in_topic2;   // state      topic
extern const char* in_topic3;   // brightness topic
extern const char* in_topic4;   // override   topic
extern const char* in_topic5;   // RGBW       topic **only works in override mode**
extern const char* in_topic6;   // flash      topic **only works in override mode**

extern char MQTT_heartbeat[60];
extern char clientoutput1[60];
extern char clientoutput2[60];
extern char clientoutput3[60];

extern char clientinput1[60];
extern char clientinput2[60];
extern char clientinput3[60];
extern char clientinput4[60];
extern char clientinput5[60];
extern char clientinput6[60];

extern char connectphrase[140];     // publishes to 'outTopic' when connected
extern String IPaddress;            // IP address for 'outTopic'
// extern char mqtt_button_buffer[40]; // message from button buffer
// extern char mqtt_amp_buffer[100];   // message from INA buffer
// extern char mqtt_volt_buffer[40];   // message from Volts buffer

// extern const uint8_t mqtt_lwt_qos;
// extern const uint8_t mqtt_lwt_retain;

/* mqtt config input */
extern uint8_t  mqttC;           // what port to change
extern uint16_t mqttCur;         // current that a port is being set to
extern String   mqttState;       // state that a port is being set to
extern uint8_t  rednew[5]; // new LED color for override MODE     -- RED
extern uint8_t  grnnew[5]; // new LED color for override MODE     -- GREEN
extern uint8_t  blunew[5]; // new LED color for override MODE     -- BLUE
extern uint8_t  whinew[5]; // new LED color for override MODE     -- WHITE
 
 //////////////////////////////////////
 // From config.h
 //////////////////////////////////////

// extern uint16_t    portcurrent[4];  // max current for a port - max 3A (parts limit) // over ridden by config above


/* Varibles here are filled in by the config system */
extern char        host[32];
extern char        ssid[32];
extern char        password[64];

extern char        AP_SSID[32];
extern char        AP_PASS[64];
extern uint8_t     AP_CHANNEL; // not written over
extern uint8_t     AP_HIDDEN;
extern uint8_t     AP_MAX_CON; // not written over

extern char        mqtt_broker[32];
extern uint16_t    mqtt_port;
extern char        mqtt_username[32];
extern char        mqtt_password[32];

extern uint8_t     darkState;
extern char        htmltitle[32];
extern char        htmltype[32];
extern char        htmlcolor[10];
extern char        htmlhover[10];

// extern uint16_t    systemcurrent;         // max current availble to the system (accounts for esp usage)***
// extern uint16_t    portcurrent0;          // max current for a port - max 3A (parts limit) // will be used in json config
// extern uint16_t    portcurrent1;          // max current for a port - max 3A (parts limit) // will be used in json config
// extern uint16_t    portcurrent2;          // max current for a port - max 3A (parts limit) // will be used in json config
// extern uint16_t    portcurrent3;          // max current for a port - max 3A (parts limit) // will be used in json config

extern uint8_t     brightness;            // set strip brightness

// extern uint8_t     overrideMODE;          // are we allowing local control or only mqtt?
// extern uint8_t     overrideWEB;           // can the web interface control the hub?
 
 //////////////////////////////////////
 // From factory_settings.h
 //////////////////////////////////////

/* Device name / hostname - Hostname may not work on all DCHP setups - HOSTNAME IS USED WITH MQTT TOPICS*/
extern char       hostFACTORY[32];

/* WIFI */
extern char       ssidFACTORY[32];            // unconfigured ssid
extern char       passwordFACTORY[64];            // wifi password

/* AP */
extern char       AP_SSIDFACTORY[32];           // will revert to using host
extern char       AP_PASSFACTORY[64]; // AP password                                   *** Minimum 8 charcter value max 63 (64 with \n)
extern uint8_t    AP_HIDDENFACTORY;             // AP SSID brodcast                              hidden = 1

/* MQTT */
extern char       mqtt_brokerFACTORY[32];            // IP address or host name of your MQTT broker
extern uint16_t   mqtt_portFACTORY;           // port for MQTT broker
extern char       mqtt_usernameFACTORY[32];            // undefined username for mqtt                   won't use a username or password in this case
extern char       mqtt_passwordFACTORY[32];            // template password for mqtt user

/* HTML */
extern uint8_t   darkStateFACTORY;
extern char      htmltitleFACTORY[32];      // main title on the top of webpage          
extern char      htmltypeFACTORY[32];      // Device type on the bottom of webpage     
extern char      htmlcolorFACTORY[10];      // main HTML webpage color                       Superhouse.tv color
extern char      htmlhoverFACTORY[10];      // html color for hovering over a menu button    Superhouse.tv color

/* smartHUB*/
// extern uint16_t    systemcurrentFACTORY;             // max current availble to the system - max 5A (parts limit)  -- rating of power supply
// extern uint16_t    portcurrent0FACTORY;             // max current for a port             - max 3A (parts limit)  // will be used in json config
// extern uint16_t    portcurrent1FACTORY;             // max current for a port             - max 3A (parts limit)  // will be used in json config
// extern uint16_t    portcurrent2FACTORY;             // max current for a port             - max 3A (parts limit)  // will be used in json config
// extern uint16_t    portcurrent3FACTORY;             // max current for a port             - max 3A (parts limit)  // will be used in json config

extern uint8_t     brightnessFACTORY;               // set strip brightness

// extern uint8_t     overrideMODEFACTORY;            // are we allowing local control or only mqtt?
// extern uint8_t     overrideWEBFACTORY;            // can the web interface control the hub?
