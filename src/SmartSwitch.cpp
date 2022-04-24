/*
 * Heavily mutilated code ripped violently from 
 * https://github.com/austinscreations/smart-usb-hub
 */

#include "LIBRARIES.h"

#include "DEFINES.h"
#include "varibles.h"         // non-edited varibles

#include "config.h"           // config information
#include "factory_settings.h" // factory reset config
#include "wifisave.h"         // Saving new Config information              should be cpp

#include "wifi.h"             // manages the wifi and AP conenctions        should be cpp
#include "MQTT.h"             // emdedded functions for wifi and mqtt       should be cpp

#include "neopixel.h"         // embedded animations for neopixels          should be cpp
#include "ESP_Color.h"        // embede library for changing RGB - HSV - HEX for webpage
#include "customserver.h"     // manages the ASYNC server webpage serving   should be cpp
#include "processing_items.h" // processor for webpage varibles             should be cpp
#include "web_json.h"         // embedded handling of websocket json

#include "DEVICE_SPECIFIC.h"  // PreProcessor macros & stuff for the current project

void setup()
{
  setup_DEBUG();
  DEBUG_Title();

  DEBUG_Reset();              // print reset reason

  parameterSETUP();           // wifisave.h

  PIXELS_init();

  wifi_start();               // start wifi   - will start AP / WiFi as needed - wifi.h

  initWebSocket();            // start websocket

  customInit();               // start server - starts ASYNC server - customserver.h

  MQTT_init();

  /////////////////////////////////////////////
  //  Configuration for the current project  //
  /////////////////////////////////////////////
  DEVICE_SETUP();
  /////////////////////////////////////////////

  DEBUG_Ready();              // prints running ; as most items are setup at this point
}

void loop()
{
  WEB_cleanupClients();

  wifi_checkup();             // checks if wifi is still connected and starts AP as needed - wifi.h
  
  if (restartRequired)        // checks if the esp needs a reboot
  { // - done via webpage / OTA - customserver.h
    OTA_Restart();
  }
 
  if (factoryRequired)        // checks if the esp needs a factory reset
  { // - done via webpage / OTA - customserver.h and wifisave.h
    deleteData();
  }

  if (WiFi.status() == WL_CONNECTED) // check that we are connected to wifi before attempting mqtt
  {
    if (strcmp(mqtt_broker, "0") == 0) // no broker declared
    {
    }
    else // broker declared
      MQTT_loop();
  }

  if (connected_update == true) // if we are conencted to wifi and mqtt go green briefly
  {
    PIXELS_success();
  }

  if (ws_connected != 0) // we have a websocket client connected - send it data
  {
    if ((millis() - lastUpdate) > 500) // waiting an amount of time before resending
    {
      webSENDjson(); // web_json.h - send json for websocket
    }
  }

  /////////////////////////////////////////////
  // Actions for the current project         //
  /////////////////////////////////////////////
  DEVICE_LOOP();
  /////////////////////////////////////////////

} // end main loop

//////////////////////////////////////////////////////////////////////////
//  This exists just to make life easier with DEVICE_SPECIFIC.h         //
//  (Just in case one of the device functions doesn't really exist...)  //
//////////////////////////////////////////////////////////////////////////
void NULL_function() {}
