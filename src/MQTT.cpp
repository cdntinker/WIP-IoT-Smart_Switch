// mqtt setup information

// #include "LIBRARIES.h"
#include "EXTERNS.h"
#include "DEFINES.h"

#include "Tinker_DEBUG.h"

#include "MQTT.h"
#include "neopixel.h"
#include "web_json.h"
#include "wifisave.h"

#include <PubSubClient.h> // For MQTT

WiFiClient espClient;
PubSubClient MQTT_client(espClient);
extern char DEBUGtxt[92];

#define MQTT_BUFFER_SIZE (64) // This number is arbitrary
                               // MQTT_command can be up to 65,536 bytes
                               // MQTT_msg_in can be up to 268,435,456 bytes
                               // (it's 64 ATM just to make stuff fit in DEBUGtxt)

  char MQTT_outTopic[MQTT_BUFFER_SIZE];
  char MQTT_inTopic[MQTT_BUFFER_SIZE];
  char MQTT_teleTopic[MQTT_BUFFER_SIZE];
  char MQTT_statTopic[MQTT_BUFFER_SIZE];

  // const char MQTT_ClientName[] = STR(DeviceName);
   char MQTT_ClientName[32];

void MQTT_init()
{
  DEBUG_Init("MQTT");

  strcpy(MQTT_ClientName, host);

  if (strcmp(mqtt_broker, "0") == 0) // no broker declared
  {
    DEBUG_Trouble("no broker declared");
  }
  else // broker declared
  {
    MQTT_settopics(); // mqtt_setup.h - set mqtt topics
    MQTT_client.setServer(mqtt_broker, mqtt_port);
    MQTT_client.setCallback(MQTT_callback);
  }
}

void MQTT_settopics()
{ // sets mqtt topics based on hostname
  DEBUG_Init("MQTT Topics");

//////////////////////////////////////////////////
//  From TinkerLibs_MQTT
//////////////////////////////////////////////////
DEBUG_Success("+++ Tinkers Topics +++");
// #define MQTT_BUFFER_SIZE (64) // This number is arbitrary
//                                // MQTT_command can be up to 65,536 bytes
//                                // MQTT_msg_in can be up to 268,435,456 bytes
//                                // (it's 64 ATM just to make stuff fit in DEBUGtxt)

//   char MQTT_outTopic[MQTT_BUFFER_SIZE];
//   char MQTT_inTopic[MQTT_BUFFER_SIZE];
//   char MQTT_teleTopic[MQTT_BUFFER_SIZE];
//   char MQTT_statTopic[MQTT_BUFFER_SIZE];

  // char MQTT_msg_out[MQTT_BUFFER_SIZE *10];

sprintf(DEBUGtxt, "ClientName: %s", MQTT_ClientName);
DEBUG_LineOut(DEBUGtxt);

  //  Build the topic names
  strcpy(MQTT_heartbeat, MQTT_ClientName);
  strcat(MQTT_heartbeat, "/LWT");

sprintf(DEBUGtxt, "MQTT_heartbeat: %s", MQTT_heartbeat);
DEBUG_LineOut(DEBUGtxt);

  strcpy(MQTT_inTopic, "cmnd/"); //  in - Commands
  strcat(MQTT_inTopic, MQTT_ClientName);
  strcat(MQTT_inTopic, "/#");

sprintf(DEBUGtxt, "MQTT_inTopic:   %s", MQTT_inTopic);
DEBUG_LineOut(DEBUGtxt);

  strcpy(MQTT_teleTopic, "tele/"); // out - Telemetry
  strcat(MQTT_teleTopic, MQTT_ClientName);

sprintf(DEBUGtxt, "MQTT_teleTopic: %s/#", MQTT_teleTopic);
DEBUG_LineOut(DEBUGtxt);

  strcpy(MQTT_statTopic, "stat/"); // out - Status
  strcat(MQTT_statTopic, MQTT_ClientName);

sprintf(DEBUGtxt, "MQTT_statTopic: %s/#", MQTT_statTopic);
DEBUG_LineOut(DEBUGtxt);

  strcpy(MQTT_outTopic, "noti/"); // out - Notifications
  strcat(MQTT_outTopic, MQTT_ClientName);

sprintf(DEBUGtxt, "MQTT_outTopic:  %s/#", MQTT_outTopic);
DEBUG_LineOut(DEBUGtxt);

  //////////////////////////////////////////////////
DEBUG_Trouble("+++ Austins Topics +++");

  // *** outputs *** //
  // strcpy(MQTT_heartbeat, host);
  // strcat(MQTT_heartbeat, "/LWT");

  // strcpy(clientoutput1, host);
  // strcat(clientoutput1, "/button");

  // strcpy(clientoutput2, host);
  // strcat(clientoutput2, "/port");

  // strcpy(clientoutput3, host);
  // strcat(clientoutput3, "/volt");

  // // *** inputs ***  //
  // strcpy(clientinput1, host);
  // strcat(clientinput1, "/current");

  // /* used in normal mode */
  // strcpy(clientinput2, host);
  // strcat(clientinput2, "/state");

  strcpy(clientinput3, host);
  strcat(clientinput3, "/brightness");

  // strcpy(clientinput4, host);
  // strcat(clientinput4, "/override");

  strcpy(clientinput5, host);
  strcat(clientinput5, "/rgbw");

  strcpy(clientinput6, host);
  strcat(clientinput6, "/flash");

  out_heart = MQTT_heartbeat;
  // out_topic1 = clientoutput1;     //
  // out_topic2 = clientoutput2;     //
  // out_topic3 = clientoutput3;     //
  // in_topic1 = clientinput1;
  // in_topic2 = clientinput2;
  in_topic3 = clientinput3;
  // in_topic4 = clientinput4;
  in_topic5 = clientinput5;
  in_topic6 = clientinput6;

  DEBUG_LineOut2(out_heart);
  DEBUG_LineOut("*** OUTPUTS ***");
  // DEBUG_LineOut2(out_topic1);       //
  // DEBUG_LineOut2(out_topic2);       //
  // DEBUG_LineOut2(out_topic3);       //
  DEBUG_LineOut("*** INPUTS ***");
  // DEBUG_LineOut2(in_topic1);
  // DEBUG_LineOut2(in_topic2);
  DEBUG_LineOut2(in_topic3);
  // DEBUG_LineOut2(in_topic4);
  DEBUG_LineOut2(in_topic5);
  DEBUG_LineOut2(in_topic6);
  DEBUG_LineOut("*** Flash Control ***");
  DEBUG_LineOut2("flash");
}

void MQTT_callback(char *MQTT_topic, byte *MQTT_payload, unsigned int length)
{
  sprintf(DEBUGtxt, "MQTT_msg_in arrived [%s] ", MQTT_topic);
  DEBUG_LineOut(DEBUGtxt);

  MQTT_payload[length] = '\0';
  sprintf(DEBUGtxt, "MQTT_payload:[%s] ", (char *)MQTT_payload);
  DEBUG_LineOut2(DEBUGtxt);

//////////////////////////////////////////////////
//  From TinkerLibs_MQTT
//////////////////////////////////////////////////

    // char MQTT_msg_in[MQTT_BUFFER_SIZE];
    char MQTT_msg_in[28]; // Limiting size for DEBUG functions...

    char *MQTT_command = strrchr(MQTT_topic, '/');
    char CNasT[MQTT_BUFFER_SIZE];
    strcpy(CNasT, "/");
    strcat(CNasT, MQTT_ClientName); // "ClientName as MQTT_command"

    DEBUG_SectionTitle("MQTT_msg_in arrived");
    sprintf(DEBUGtxt, "MQTT_command: %30s", MQTT_command);
    DEBUG_LineOut(DEBUGtxt);

    // if (length < MQTT_BUFFER_SIZE)
    // if (length < 63)
    // Messages 63 characters long or bigger make BOOM
    // with a "Soft WDT reset"
    // MQTT_BUFFER_SIZE is 100
    // I R cornfoozed...
    if (length < 59) // & now 59 is bad...  :|
    {

        MQTT_msg_in[0] = '\0'; // start with an empty string!
        for (int i = 0; i < length; i++)
        {
            MQTT_msg_in[i] = (char)MQTT_payload[i];
            MQTT_msg_in[i + 1] = '\0';
        }

        sprintf(DEBUGtxt, "MQTT_msg_in: %28s", MQTT_msg_in);
        DEBUG_LineOut(DEBUGtxt);
        sprintf(DEBUGtxt, "MQTT_msg_in Size: %d", length);
        DEBUG_LineOut(DEBUGtxt);

        /////////////////////////////////////////////////////
        // MQTT_msg_in handling goes here...
        /////////////////////////////////////////////////////

        if (strcmp(MQTT_command, CNasT) == 0) // MQTT_ClientName as MQTT_command
        {
            DEBUG_Trouble("Missing topic...");
            MQTT_SendNOTI("Error", "Missing topic...");
        }

        /*********************************************************************
         * This is where you need to send the incoming message off
         * to be handled elsewhere.
         * Probably in your main project code would be best...
         * 
         * Need a standardised function call. (should be in main project...)
         * void MQTT_HandleMessages(const char *MQTT_command, const char *MQTT_msg_in)
         *********************************************************************/
        else
        {
            MQTT_HandleMessages(MQTT_command, MQTT_msg_in);
        }
    }
    else
    {
        DEBUG_Trouble("But, it's TOO Bloody Big!");
        MQTT_SendNOTI("Error", "MQTT_msg_in TOO Big!");
    }
    //////////////////////////////////////////////////

  // if (strcmp(MQTT_topic, "flash") == 0) // flash rate for leds
  // {
  //   if ((char)MQTT_payload[0] == '1')
  //   {
  //     ledState = HIGH;
  //   } // on
  //   if ((char)MQTT_payload[0] == '0')
  //   {
  //     ledState = LOW;
  //   } // off
  //   if (overrideMODE == true)
  //   {
  //     for (uint8_t y = 0; y < 4; y++) // check all the override led states
  //     {
  //       if (ledmode[y] == 2) // we are in a flash state so make sure we do regular updates on websocket
  //       {
  //         if (ws_connected != 0)
  //         {
  //           webSENDjson();
  //         }
  //       }
  //     }
  //   }
  // }

  // if (strcmp(MQTT_topic, in_topic4) == 0) // request to activate override mode
  // {
  //   if ((char)MQTT_payload[0] == '1') // override active - all hub control goes through mqtt
  //   {
  //     overrideMODE = true;
  //     for (uint8_t y = 0; y < 4; y++) // resetting all 4 led colors
  //     {
  //       ledmode[y] = {0}; // what mode the leds are in           -- used in overrideMODE control
  //       rednew[y] = {0};  // new LED color for override MODE     -- RED
  //       grnnew[y] = {0};  // new LED color for override MODE     -- GREEN
  //       blunew[y] = {0};  // new LED color for override MODE     -- BLUE
  //       whinew[y] = {0};  // new LED color for override MODE     -- WHITE
  //     }
  //   }
  //   if ((char)MQTT_payload[0] == '0')
  //   {
  //     overrideMODE = false;
  //   } // override NOT active - hub can be controlled locally
  // }

  // if (strcmp(MQTT_topic, in_topic1) == 0) // call to configure per port current
  // {
  //
  //   String value = String((char *)MQTT_payload);
  //
  //   int iStart, iEnd;
  //   iStart = 0;
  //   iEnd = value.indexOf(',', iStart);
  //   mqttC = value.substring(iStart, iEnd).toInt();
  //   iStart = iEnd + 1;
  //   iEnd = value.indexOf(',', iStart);
  //   mqttCur = value.substring(iStart, iEnd).toInt();
  //
  //   if (mqttC != 0)
  //   {
  //     if (mqttC > 4)
  //     {
  //       DEBUG_Trouble("We only have 4 ports to configure - change your value");
  //     }
  //     else
  //     {
  //       if (mqttCur > 3000)
  //       {
  //         DEBUG_Trouble("Max port current is 3000mA - setting to max");
  //         mqttCur = 3000;
  //       }
  //       if (mqttCur < 0)
  //       {
  //         DEBUG_Trouble("Current Limit can't be negative - setting to 0");
  //         mqttCur = 0;
  //       }
  //
  //       /* need for future use */
  //       if (mqttC == 1)
  //       {
  //         portcurrent0 = mqttCur;
  //       }
  //       if (mqttC == 2)
  //       {
  //         portcurrent1 = mqttCur;
  //       }
  //       if (mqttC == 3)
  //       {
  //         portcurrent2 = mqttCur;
  //       }
  //       if (mqttC == 4)
  //       {
  //         portcurrent3 = mqttCur;
  //       }
  //
  //       portcurrent[(mqttC - 1)] = mqttCur;
  //       sprintf(DEBUGtxt, "Port %d Current Set to: %dmA", mqttC, mqttCur);
  //       DEBUG_LineOut(DEBUGtxt);
  //
  //       DEBUG_Separator();
  //       saveConfignew(); // save the config
  //     }
  //   }
  //   else
  //   {
  //     DEBUG_Trouble("Ports are 1-based number - change your value");
  //   }
  // } // end of per port mqtt config

  // if (strcmp(MQTT_topic, in_topic2) == 0) // request to change port state
  // {
  //
  //   String value = String((char *)MQTT_payload);
  //
  //   int iStart, iEnd;
  //   iStart = 0;
  //   iEnd = value.indexOf(',', iStart);
  //   mqttC = value.substring(iStart, iEnd).toInt();
  //   iStart = iEnd + 1;
  //   iEnd = value.indexOf(',', iStart);
  //   //     mqttState = value.substring(iStart, iEnd).c_str();
  //   mqttState = value.substring(iStart, iEnd);
  //   //     strcpy(clientoutput1, host);
  //
  //   // override changes neopixel update
  //   if (mqttC != 0)
  //   {
  //     if (mqttC > 4)
  //     {
  //       DEBUG_Trouble("We only have 4 ports to configure - change your value");
  //     }
  //     else
  //     {
  //       sprintf(DEBUGtxt, "Setting Port %d", mqttC);
  //       DEBUG_LineOut(DEBUGtxt);
  //
  //       if (mqttState == "off")
  //       {
  //         if (port_state[(mqttC - 1)] != 0 && voltlockout == 0) // not already off or in over / under current / voltage state
  //         {
  //           if (port_state[(mqttC - 1)] == 11) // over current on hub
  //           {
  //             for (uint8_t y = 0; y < 4; y++) // resetting all 4 port states
  //             {
  //               port_state[y] = 0; // this is actully setting all ports off
  //             }
  //             DEBUG_LineOut(" HUB State To: off");
  //           }
  //           else // other wise we are jsu tsetting a port off (or reseting that port from over current)
  //           {
  //             port_state[(mqttC - 1)] = 0; // turn this port off / reset
  //             DEBUG_LineOut(" State To: off");
  //           }
  //           if (overrideMODE == false)
  //           {
  //             neo_update[(mqttC - 1)] = true;
  //           }                               // update leds directly if we aren't in override mode
  //           mcp_update[(mqttC - 1)] = true; // ensure mcp's update
  //         }
  //       }
  //       else if (mqttState == "power")
  //       {
  //         if (port_state[(mqttC - 1)] != 1 && port_state[(mqttC - 1)] != 10 && port_state[(mqttC - 1)] != 11 && voltlockout == 0) // not already off or in over / under current / voltage state
  //         {
  //           DEBUG_LineOut(" State To: power");
  //           port_state[(mqttC - 1)] = 1;
  //           if (overrideMODE == false)
  //           {
  //             neo_update[(mqttC - 1)] = true;
  //           }                                    // update leds directly if we aren't in override mode
  //           mcp_update[(mqttC - 1)] = true;      // ensure mcp's update
  //           lastINAread[(mqttC - 1)] = millis(); // resets the time readout for reading current usage
  //           lastINAmqtt[(mqttC - 1)] = millis(); // resets the time for the for mqtt current readout
  //         }
  //       }
  //       else if (mqttState == "data")
  //       {
  //         if (port_state[(mqttC - 1)] != 2 && port_state[(mqttC - 1)] != 10 && port_state[(mqttC - 1)] != 11 && voltlockout == 0) // not already off or in over / under current / voltage state
  //         {
  //           DEBUG_LineOut(" State To: data");
  //           port_state[(mqttC - 1)] = 2;
  //           if (overrideMODE == false)
  //           {
  //             neo_update[(mqttC - 1)] = true;
  //           }                                    // update leds directly if we aren't in override mode
  //           mcp_update[(mqttC - 1)] = true;      // ensure mcp's update
  //           lastINAread[(mqttC - 1)] = millis(); // resets the time readout for reading current usage
  //           lastINAmqtt[(mqttC - 1)] = millis(); // resets the time for the for mqtt current readout
  //         }
  //       }
  //       else
  //       {
  //         DEBUG_Trouble("Not a valid state");
  //         sprintf(DEBUGtxt, "Attemped State: %s", mqttState.c_str());
  //         DEBUG_Trouble(DEBUGtxt);
  //       }
  //     }
  //   }
  //   else
  //   {
  //     DEBUG_Trouble("Ports are 1-based number - change your value");
  //   }
  //
  // } // end of change port state

  if (strcmp(MQTT_topic, in_topic3) == 0) // request to change LED brightness
  {
    String value = String((char *)MQTT_payload);

    if (value.toInt() >= 0 && value.toInt() <= 255)
    {
      brightness = value.toInt();
      PIXELS_brightness();
      // strip.setBrightness(brightness);
      // if (overrideMODE == false) // not in overrideMODE - update LED brightness normally
      // {
      //   for (int a = 0; a < 4; a++)
      //   {
      //     neo_update[a] = true; // time to update the neopixel
      //   }
      // }
      // else // in overrideMODE - update the LED's accordingly
      // {
      //   for (int a = 0; a < 4; a++)
      //   {
      //     neo_override[a] = true; // time to update the neopixel in override mode
      //   }
      // }
      sprintf(DEBUGtxt, "brightness set to: %d", brightness);
      DEBUG_LineOut(DEBUGtxt);
    }
    else
    {
      DEBUG_Trouble("incompatible LED brightness level - 0-255 allowed");
      sprintf(DEBUGtxt, "recieved value: %s", value.c_str());
    }
  } // end of change LED brightness

  if (strcmp(MQTT_topic, in_topic5) == 0) // call to set regular rgbw color
  {

    String value = String((char *)MQTT_payload);

    int iStart, iEnd;
    iStart = 0;
    iEnd = value.indexOf(',', iStart);
    mqttC = value.substring(iStart, iEnd).toInt();

    if (mqttC != 0)
    {
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      rednew[(mqttC - 1)] = value.substring(iStart, iEnd).toInt();
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      grnnew[(mqttC - 1)] = value.substring(iStart, iEnd).toInt();
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      blunew[(mqttC - 1)] = value.substring(iStart, iEnd).toInt();
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      whinew[(mqttC - 1)] = value.substring(iStart, iEnd).toInt();

      sprintf(DEBUGtxt, "LED #: %d", mqttC);
      DEBUG_LineOut(DEBUGtxt);

      sprintf(DEBUGtxt, "RED: %d", rednew[(mqttC - 1)]);
      DEBUG_LineOut(DEBUGtxt);

      sprintf(DEBUGtxt, "GREEN: %d", grnnew[(mqttC - 1)]);
      DEBUG_LineOut(DEBUGtxt);

      sprintf(DEBUGtxt, "BLUE: %d", blunew[(mqttC - 1)]);
      DEBUG_LineOut(DEBUGtxt);

      sprintf(DEBUGtxt, "WHITE: %d", whinew[(mqttC - 1)]);
      DEBUG_LineOut(DEBUGtxt);

      ledmode[(mqttC - 1)] = 1;         // set led to normal color
      neo_override[(mqttC - 1)] = true; // time to update the neopixel
      if (ws_connected != 0)
      {
        webSENDjson();
      }
    }
    else
    {
      DEBUG_Trouble("LED's are 1-based number - change your value");
    }
  } // end of rgbw color set

  if (strcmp(MQTT_topic, in_topic6) == 0) // call to set RGB color with flash enabled
  {

    String value = String((char *)MQTT_payload);

    int iStart, iEnd;
    iStart = 0;
    iEnd = value.indexOf(',', iStart);
    mqttC = value.substring(iStart, iEnd).toInt();

    // ****************************************add provisions for lockout modes
    if (mqttC != 0)
    {
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      rednew[(mqttC - 1)] = value.substring(iStart, iEnd).toInt();
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      grnnew[(mqttC - 1)] = value.substring(iStart, iEnd).toInt();
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      blunew[(mqttC - 1)] = value.substring(iStart, iEnd).toInt();
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      whinew[(mqttC - 1)] = value.substring(iStart, iEnd).toInt();

      sprintf(DEBUGtxt, "LED #: %d", mqttC);
      DEBUG_LineOut(DEBUGtxt);

      sprintf(DEBUGtxt, "RED: %d", rednew[(mqttC - 1)]);
      DEBUG_LineOut(DEBUGtxt);

      sprintf(DEBUGtxt, "GREEN: %d", grnnew[(mqttC - 1)]);
      DEBUG_LineOut(DEBUGtxt);

      sprintf(DEBUGtxt, "BLUE: %d", blunew[(mqttC - 1)]);
      DEBUG_LineOut(DEBUGtxt);

      sprintf(DEBUGtxt, "WHITE: %d", whinew[(mqttC - 1)]);
      DEBUG_LineOut(DEBUGtxt);

      ledmode[(mqttC - 1)] = 2; // set led to normal color
      if (ws_connected != 0)
      {
        webSENDjson();
      }
    }
    else
    {
      DEBUG_Trouble("LED's are 1-based number - change your value");
    }
  } // end of flash color set

} // end of mqtt MQTT_callback

#include "Tinker_SmartSwitch.h"
#include "DEVICE_SPECIFIC.h"

void MQTT_HandleMessages(const char *MQTT_command, const char *MQTT_msg_in)
// {

// }
// void MQTT_HandleMessages(const char *MQTT_command, const char MQTT_msg_in[MQTT_BUFFER_SIZE])
{
    if (strcmp(MQTT_command, "/Power") == 0)
    {
        // MQTT_SendTELE(MQTT_command, MQTT_command);
        MQTT_SendNOTI("triggered", "Power!!!");
        if (strcmp(MQTT_msg_in, "on") == 0)
            SmartSwitch_Relay(HIGH);
        if (strcmp(MQTT_msg_in, "off") == 0)
            SmartSwitch_Relay(LOW);
        if (strcmp(MQTT_msg_in, "toggle") == 0)
            SmartSwitch_Toggle();
        // SmartSwitch_Relay(!SmartSwitch_PWR_STATE);
    }
    else if (strcmp(MQTT_command, "/LED01") == 0)
    {
        // MQTT_SendTELE(MQTT_command, MQTT_command);
        MQTT_SendNOTI("triggered", "LED01!!!");
        if (strcmp(MQTT_msg_in, "on") == 0)
            SmartSwitch_LED(HIGH);
        if (strcmp(MQTT_msg_in, "off") == 0)
            SmartSwitch_LED(LOW);
        if (strcmp(MQTT_msg_in, "toggle") == 0)
            DEVICE_LED01(!SmartSwitch_LED01_STATE);
    }
    else if (strcmp(MQTT_command, "/LED02") == 0)
    {
        // MQTT_SendTELE(MQTT_command, MQTT_command);
        MQTT_SendNOTI("triggered", "LED02!!!");
        if (strcmp(MQTT_msg_in, "on") == 0)
            SmartSwitch_LINKLED(HIGH);
        if (strcmp(MQTT_msg_in, "off") == 0)
            SmartSwitch_LINKLED(LOW);
        if (strcmp(MQTT_msg_in, "toggle") == 0)
            DEVICE_LED02(!SmartSwitch_LED02_STATE);
    }
    else if (strcmp(MQTT_command, "/Status") == 0)
    {
        MQTT_SendNOTI("triggered", "Status!!!");
        DEBUG_LineOut("Status Requested");
        if (strcmp(MQTT_msg_in, "Power") == 0)
        {
            MQTT_SendSTAT("Power", SmartSwitch_PWR_STATE ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "LED01") == 0)
        {
            MQTT_SendSTAT("LED01", SmartSwitch_LED01 ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "LNKLD") == 0)
        {
            MQTT_SendSTAT("LNKLD", SmartSwitch_LED02 ? "ON" : "OFF");
        }
        else if (strcmp(MQTT_msg_in, "All") == 0)
        {
            MQTT_SendSTAT("Power", SmartSwitch_PWR_STATE ? "ON" : "OFF");
            MQTT_SendSTAT("LED01", SmartSwitch_LED01 ? "ON" : "OFF");
            MQTT_SendSTAT("LNKLD", SmartSwitch_LED02 ? "ON" : "OFF");
        }
        // else if (strcmp(MQTT_msg_in, "All") == 0)

    }

    else
    {
        DEBUG_Trouble("Dunno Whatcha want...");
        MQTT_SendNOTI("Error", "Dunno Whatcha want...");
    }
}

void MQTT_reconnect()
{

  // Loop until we're reconnected
  // while (!MQTT_client.connected())
  // {
  PIXELS_colorWipe(0, 0, 0, 220);

  DEBUG_Init("Attempting MQTT connection...");
  if (MQTT_client.connect(host, mqtt_username, mqtt_password, out_heart, mqtt_lwt_qos, mqtt_lwt_retain, "0"))
  {
    IPaddress = WiFi.localIP().toString();
    DEBUG_Success("mqtt connected");
    connected_update = true;
    // Once connected, publish an announcement...
    strcpy(connectphrase, "connected = ");
    strcat(connectphrase, host);
    strcat(connectphrase, "  IP Address = ");
    const char *c = IPaddress.c_str();
    strcat(connectphrase, c); // ip address
    const char *phrase = connectphrase;
    MQTT_client.publish("outTopic", phrase);
    byte lwt_payload[] = {'1'};
    MQTT_client.publish(out_heart, lwt_payload, 1, mqtt_lwt_retain);
    // ... and resubscribe
    // MQTT_client.subscribe("flash");
    // MQTT_client.subscribe(in_topic1);
    // MQTT_client.subscribe(in_topic2);
    // MQTT_client.subscribe(in_topic3);
    // MQTT_client.subscribe(in_topic4);
    // MQTT_client.subscribe(in_topic5);
    // MQTT_client.subscribe(in_topic6);

    MQTT_client.subscribe(MQTT_inTopic);
  }
  else
  {
    sprintf(DEBUGtxt, "failed, rc=%d try again in 5 seconds", MQTT_client.state());
    DEBUG_Trouble(DEBUGtxt);
    //       Wait 5 seconds before retrying
    delay(5000);
  }
  // }
}

void MQTT_loop()
{
  if (!MQTT_client.connected())
  {
    MQTT_reconnect();
  }
  MQTT_client.loop();
}

void MQTT_send(const char *MQTT_command, char Buffer[40])
{
  MQTT_client.publish(MQTT_command, Buffer);
}

/* Special for UT61E */
void MQTT_JSON_send(char g_mqtt_json_topic[50], size_t msg_length, bool TF, char g_json_message_buffer[512])
{
  MQTT_client.beginPublish(g_mqtt_json_topic, msg_length, TF);
  MQTT_client.print(g_json_message_buffer);
  MQTT_client.endPublish();
}

////////////////////////////////////////////////////////////////////////////
//  These translate the TinkerLibs MQTT function calls to AustinOTA calls //
////////////////////////////////////////////////////////////////////////////

void MQTT_SendSTAT(const char *MQTT_command, const char *MQTT_msg_in)
{
  char TheTopic[128];
  char TheMessage[128];
  strcpy(TheTopic, "stat/");
  strcat(TheTopic, host);
  strcat(TheTopic, "/");
  strcat(TheTopic, MQTT_command);
  //        MQTT_SendSTAT("Power", "ON");
  //        MQTT_SendSTAT("LED01", "ON");
  //        MQTT_SendSTAT("LED02", "ON");
  strcpy(TheMessage, MQTT_msg_in);
  MQTT_send(TheTopic, TheMessage);
}

void MQTT_SendNOTI(const char *MQTT_command, const char *MQTT_msg_in)
{
  char TheTopic[128];
  char TheMessage[128];
  strcpy(TheTopic, "noti/");
  strcat(TheTopic, host);
  strcat(TheTopic, "/");
  strcat(TheTopic, MQTT_command);
  //        MQTT_SendNOTI("triggered", "Power!!!");
  //        MQTT_SendNOTI("Error", "Dunno Whatcha want...");
  strcpy(TheMessage, MQTT_msg_in);
  MQTT_send(TheTopic, TheMessage);
}

void MQTT_SendTELE(const char *MQTT_command, const char *MQTT_msg_in)
{
  char TheTopic[128];
  char TheMessage[128];
  strcpy(TheTopic, "tele/");
  strcat(TheTopic, host);
  strcat(TheTopic, "/");
  strcat(TheTopic, MQTT_command);
  strcpy(TheMessage, MQTT_msg_in);
  MQTT_send(TheTopic, TheMessage);
}
