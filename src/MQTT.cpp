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

#include "Tinker_SmartSwitch.h"
#include "DEVICE_SPECIFIC.h"

WiFiClient espClient;
PubSubClient MQTT_client(espClient);
extern char DEBUGtxt[92];

#define MQTT_BUFFER_SIZE (64) // This number is arbitrary
// MQTT_command can be up to 65,536 bytes
// MQTT_msg_in can be up to 268,435,456 bytes
// (it's 64 ATM just to make stuff fit in DEBUGtxt)

char MQTT_outTopic[MQTT_BUFFER_SIZE];
char MQTT_inTopic[MQTT_BUFFER_SIZE];
char MQTT_grpTopic[MQTT_BUFFER_SIZE];
char MQTT_teleTopic[MQTT_BUFFER_SIZE];
char MQTT_statTopic[MQTT_BUFFER_SIZE];

// const char MQTT_ClientName[] = STR(DeviceName);
char MQTT_ClientName[32];
char MQTT_GroupName[32];

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MQTT_JSON_BUFFER_SIZE (350) // This number is arbitrary unless used to send JSON messages
char DevInfo[MQTT_JSON_BUFFER_SIZE];

// "{\"deviceName\": \"%s\", \"groupName\": \"%s\", \"ip\": \"%s\", \"mac\": \"%s\", \"ssid\": \"%s\", \"wifichannel\": \"%u\",\"rssi\": %d, \"FWVersion\": \"%s %s\", \"HWVersion\": \"%s\"}",

void MQTT_BuildTattles()
{
  char DevInfo_fmt[256];
  strcpy(DevInfo_fmt, "{");
  strcat(DevInfo_fmt, "\"Device\": \"%s\", \"FriendlyName\": \"Poop\", \"GroupTopic\": \"%s\",");
  strcat(DevInfo_fmt, " \"IPAddress\": \"%s\", \"mac\": \"%s\",");
  strcat(DevInfo_fmt, " \"WiFi\": {\"SSID\": \"%s\", \"Channel\": \"%u\",\"Signal\": \"%d\"},");
  strcat(DevInfo_fmt, " \"Version\": \"%s %s\", \"Hardware\": \"%s\"");
  strcat(DevInfo_fmt, "}");

  // Serial.println("BOOGA!");
  // Serial.println(DevInfo_fmt);
  // Serial.println("BOOGA!");
  //  "{\"Device\": \"%s\", \"FriendlyName\": \"Poop\", \"GroupTopic\": \"%s\", \"IPAddress\": \"%s\", \"mac\": \"%s\", \"wifiSSID\": \"%s\", \"wifichannel\": \"%u\",\"wifisignal\": %d, \"Version\": \"%s %s\", \"Hardware\": \"%s\"}",

  snprintf(DevInfo, MQTT_JSON_BUFFER_SIZE,
           DevInfo_fmt,
           host, group,
           WiFi.localIP().toString().c_str(), WiFi.macAddress().c_str(),
           WiFi.SSID().c_str(), WiFi.channel(), WiFi.RSSI(),
           STR(DeviceName), STR(FIRMWAREVERSION), STR(DeviceType));
  // Serial.println(DevInfo);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MQTT_init()
{
  DEBUG_Init("MQTT");

  strcpy(MQTT_ClientName, host);
  strcpy(MQTT_GroupName, group);

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
  sprintf(DEBUGtxt, "ClientName: %s", MQTT_ClientName);
  DEBUG_LineOut(DEBUGtxt);

  //  Build the topic names
  strcpy(MQTT_heartbeat, "tele/");
  strcat(MQTT_heartbeat, MQTT_ClientName);
  strcat(MQTT_heartbeat, "/LWT");

  strcpy(out_DevInfo, "stat/");
  strcat(out_DevInfo, host);
  strcat(out_DevInfo, "/DevInfo");
  DevInfo_Topic = out_DevInfo;

  sprintf(DEBUGtxt, "MQTT_heartbeat: %s", MQTT_heartbeat);
  DEBUG_LineOut(DEBUGtxt);

  strcpy(MQTT_inTopic, "cmnd/"); //  in - Commands
  strcat(MQTT_inTopic, MQTT_ClientName);
  strcat(MQTT_inTopic, "/#");

  sprintf(DEBUGtxt, "MQTT_inTopic:   %s", MQTT_inTopic);
  DEBUG_LineOut(DEBUGtxt);

  strcpy(MQTT_grpTopic, "cmnd/"); //  in - Commands
  strcat(MQTT_grpTopic, MQTT_GroupName);
  strcat(MQTT_grpTopic, "/#");

  sprintf(DEBUGtxt, "MQTT_grpTopic:   %s", MQTT_grpTopic);
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
}

void MQTT_callback(char *MQTT_topic, byte *MQTT_payload, unsigned int length)
{
  char MQTT_PARSE[64];
  char MQTT_Name[64];
  // char MQTT_cmnd[64];
  sprintf(DEBUGtxt, "MQTT_msg_in arrived [%s] ", MQTT_topic);
  DEBUG_SectionTitle(DEBUGtxt);

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  strcpy(MQTT_PARSE, strchr(MQTT_topic, '/')); // This drops the first part of the topic
  strcpy(MQTT_Name, strrchr(MQTT_PARSE, '/')); // This drops all after the second part if there is more
  memmove(MQTT_Name, MQTT_Name + 1, sizeof(MQTT_Name) - 1);
  memmove(MQTT_PARSE, MQTT_PARSE + 1, sizeof(MQTT_PARSE) - 1);
  if (strcmp(MQTT_Name, MQTT_PARSE) != 0)
  {
    strcpy(MQTT_Name, MQTT_PARSE);
    for (unsigned int i = 0; i < strlen(MQTT_Name); i++)
    { // This drops all after the second part if there is more
      if (MQTT_Name[i] == '/')
        MQTT_Name[i] = '\0';
    }
  }

  sprintf(DEBUGtxt, "Device/Group: %s", MQTT_Name);
  DEBUG_LineOut2(DEBUGtxt);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  MQTT_payload[length] = '\0';
  sprintf(DEBUGtxt, "MQTT_payload: [%s] ", (char *)MQTT_payload);
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

  sprintf(DEBUGtxt, "   MQTT_command: %s", MQTT_command);
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
    for (unsigned int i = 0; i < length; i++)
    {
      MQTT_msg_in[i] = (char)MQTT_payload[i];
      MQTT_msg_in[i + 1] = '\0';
    }

    sprintf(DEBUGtxt, "MQTT_msg_in: %s (size: %d)", MQTT_msg_in, length);
    DEBUG_LineOut(DEBUGtxt);

    /////////////////////////////////////////////////////
    // MQTT_msg_in handling goes here...
    /////////////////////////////////////////////////////

    if (strcmp(MQTT_command, CNasT) == 0) // MQTT_ClientName as MQTT_command
    {
      DEBUG_Trouble("Missing topic...");
      MQTT_SendNOTI("Error", "Missing topic...");
    }
    else
    {
      /*###############################################*
       * Need to determine if this is the group topic  *
       * then handle various permutations of it.       *
       *                                               *
       * See SmartSwitch_functions.cpp                 *
       *###############################################*/
      if (strcmp(MQTT_Name, MQTT_GroupName) == 0)
      {
        DEBUG_SectionTitle("WooHoo Group call!!!");
        MQTT_BuildTattles();
        MQTT_JSON_send((char *)DevInfo_Topic, strlen(DevInfo), false, DevInfo);
        // DEBUG_BlockOut(DevInfo);
      }
      else
      {
        /*********************************************************************
         * This is where you need to send the incoming message off
         * to be handled elsewhere.
         * Probably in your main project code would be best...
         *
         * Need a standardised function call. (should be in main project...)
         * Tho...  Separate Handlers in individual libraries would be cool.
         * void DEVICE_MQTT_IN(const char *MQTT_command, const char *MQTT_msg_in)
         *********************************************************************/

        ////////////////////////////////////////////////////////////////////////////
        // Incoming message handling is done in the device/library specific       //
        // function referred to by DEVICE_MQTT_IN                                 //
        // At some point, I intend to make it possible to have multiple           //
        // sub-functions...                                                       //
        ////////////////////////////////////////////////////////////////////////////
        DEVICE_MQTT_IN(MQTT_command, MQTT_msg_in);
      }
    }
  }
  else
  {
    DEBUG_Trouble("But, it's TOO Bloody Big!");
    MQTT_SendNOTI("Error", "MQTT_msg_in TOO Big!");
  }
  //////////////////////////////////////////////////

} // end of mqtt MQTT_callback

extern unsigned int GPIO_Relay_PINS[];
extern bool GPIO_Relay_STATE[];
extern unsigned int GPIO_Relay_COUNT;

extern unsigned int GPIO_LED_PINS[];
extern bool GPIO_LED_STATE[];
extern unsigned int GPIO_LED_COUNT;

void MQTT_reconnect()
{
  PIXELS_colorWipe(0, 0, 0, 220);

  DEBUG_Init("Attempting MQTT connection...");
  if (MQTT_client.connect(host, mqtt_username, mqtt_password, MQTT_heartbeat, mqtt_lwt_qos, mqtt_lwt_retain, "Offline"))
  {
    IPaddress = WiFi.localIP().toString();
    DEBUG_Success("mqtt connected");
    connected_update = true;

    // Once connected, publish an LWT announcement...
    const char lwt_payload[10] = "Online";

    MQTT_client.publish(MQTT_heartbeat, lwt_payload, mqtt_lwt_retain);

    // ... and resubscribe
    MQTT_client.subscribe(MQTT_inTopic);
    MQTT_client.subscribe(MQTT_grpTopic);
  }
  else
  {
    sprintf(DEBUGtxt, "failed, rc=%d try again in 5 seconds", MQTT_client.state());
    DEBUG_Trouble(DEBUGtxt);
    //       Wait 5 seconds before retrying
    delay(5000);
  }
}

void MQTT_loop()
{
  // Loop until we're reconnected
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
//  These translate the TinkerLibs MQTT function calls to IdIoT calls //
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
