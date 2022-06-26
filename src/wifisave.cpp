/* saving incoming parameters from webpage config and handle factory reset */

// #ifndef wifisave_h
// #define wifisave_h

#include "DEFINES.h"
#include "EXTERNS.h"

#include "LIBRARIES.h"

#include "wifisave.h"

uint8_t new_update = false;

#if defined(ESP8266) // LittleFS used for esp8266

void deleteData()
{
  DEBUG_Init("Data Delete");
  if ((millis() - lastDelete) > 250)
  {
    LittleFS.remove("/config.json"); // Remove the file
    WiFi.disconnect(true);           // Remove SSID creds
    DEBUG_Success("Deleted Data - deleteData");
    ESP.restart();
  }
}

bool saveFACTORY()
{ // esp8266
  DEBUG_Init("Saving FACTORY Settings");
  DynamicJsonDocument json(1024);
  json["host"] = hostFACTORY;
  json["ssid"] = ssidFACTORY;
  json["password"] = passwordFACTORY;
  json["AP_SSID"] = AP_SSIDFACTORY;
  json["AP_PASS"] = AP_PASSFACTORY;
  char cstr1[1];
  itoa(AP_HIDDENFACTORY, cstr1, 10);
  json["AP_HIDDEN"] = cstr1;
  json["mqtt_broker"] = mqtt_brokerFACTORY;
  char cstr2[5];
  itoa(mqtt_portFACTORY, cstr2, 10);
  json["mqtt_port"] = cstr2;
  json["mqtt_username"] = mqtt_usernameFACTORY;
  json["mqtt_password"] = mqtt_passwordFACTORY;
  char cstr3[1];
  itoa(darkStateFACTORY, cstr3, 10);
  json["darkState"] = cstr3;
  json["htmltitle"] = htmltitleFACTORY;
  json["htmltype"] = htmltypeFACTORY;
  json["htmlcolor"] = htmlcolorFACTORY;
  json["htmlhover"] = htmlhoverFACTORY;

  char cstr12[3];
  itoa(brightnessFACTORY, cstr12, 10);
  json["brightness"] = cstr12;

  File configFile = LittleFS.open("/config.json", "w");
  if (!configFile)
  {
    DEBUG_Trouble("failed to open config file for writing - saveFACTORY");
    return false;
  }

  if (DEBUG_JSON)
  {
    serializeJson(json, Serial);
  }
  serializeJson(json, configFile);

  configFile.close();
  //end save
  DEBUG_Success("Saved FACTORY Settings - saveFACTORY");
  DEBUG_Separator();
  return true;
}

bool saveConfignew()
{ // esp8266
  DEBUG_Init("saving NEW config");
  DynamicJsonDocument json(1024);
  json["host"] = host;
  json["ssid"] = ssid;
  json["password"] = password;
  json["AP_SSID"] = AP_SSID;
  json["AP_PASS"] = AP_PASS;
  char cstr1[1];
  itoa(AP_HIDDEN, cstr1, 10);
  json["AP_HIDDEN"] = cstr1;
  json["mqtt_broker"] = mqtt_broker;
  char cstr2[8];
  itoa(mqtt_port, cstr2, 10);
  json["mqtt_port"] = cstr2;
  json["mqtt_username"] = mqtt_username;
  json["mqtt_password"] = mqtt_password;
  char cstr3[1];
  itoa(darkState, cstr3, 10);
  json["darkState"] = cstr3;
  json["htmltitle"] = htmltitle;
  json["htmltype"] = htmltype;
  json["htmlcolor"] = htmlcolor;
  json["htmlhover"] = htmlhover;

  char cstr12[3];
  itoa(brightness, cstr12, 10);
  json["brightness"] = cstr12;

  File configFile = LittleFS.open("/config.json", "w");
  if (!configFile)
  {
    DEBUG_Trouble("failed to open config file for writing - saveConfignew");
    return false;
  }

  if (DEBUG_JSON)
  {
    serializeJson(json, Serial);
  }
  serializeJson(json, configFile);

  configFile.close();
  //end save
  DEBUG_Success("Saved NEW Settings - saveConfignew");
  DEBUG_Separator();
  return true;
}

bool loadConfig()
{ // esp8266
  DEBUG_Init("Config");
  if (LittleFS.exists("/config.json"))
  {
    //file exists, reading and loading
    DEBUG_Success("loadConfig: reading config file");
    File configFile = LittleFS.open("/config.json", "r");

    if (configFile)
    {
      DEBUG_Success("loadConfig: opened config file");
      size_t size = configFile.size();
      // Allocate a buffer to store contents of the file.
      std::unique_ptr<char[]> buf(new char[size]);

      configFile.readBytes(buf.get(), size);

      DynamicJsonDocument json(1024);
      auto deserializeError = deserializeJson(json, buf.get());
      if (DEBUG_JSON)
      {
        serializeJson(json, Serial);
      }
      if (!deserializeError)
      {

        strcpy(host, json["host"]);
        strcpy(ssid, json["ssid"]);
        strcpy(password, json["password"]);
        strcpy(AP_SSID, json["AP_SSID"]);
        strcpy(AP_PASS, json["AP_PASS"]);
        String convert1 = json["AP_HIDDEN"];
        AP_HIDDEN = convert1.toInt();
        strcpy(mqtt_broker, json["mqtt_broker"]);
        String convert2 = json["mqtt_port"];
        mqtt_port = convert2.toInt();
        strcpy(mqtt_username, json["mqtt_username"]);
        strcpy(mqtt_password, json["mqtt_password"]);
        String convert3 = json["darkState"];
        darkState = convert3.toInt();
        strcpy(htmltitle, json["htmltitle"]);
        strcpy(htmltype, json["htmltype"]);
        strcpy(htmlcolor, json["htmlcolor"]);
        strcpy(htmlhover, json["htmlhover"]);

        String convert12 = json["brightness"];
        brightness = convert12.toInt();
      }
      else
      {
        DEBUG_Trouble("loadConfig: failed to load json config");
        return false;
      }
      configFile.close();
      DEBUG_Success("loadConfig: file closed");
      return true;
    }
  }
  DEBUG_Trouble("loadConfig: config file doesn't exist");
  return false;
}

#elif defined(ESP32) // LITTLEFS used for esp32

void deleteData() // LITTLEFS used for esp32
{
  DEBUG_Init("Data Delete");
  if ((millis() - lastDelete) > 250)
  {
    LITTLEFS.remove("/config.json"); // Remove the file
    WiFi.disconnect(true);           // Remove SSID creds
    DEBUG_Success("Deleted Data - deleteData");
    // ESP32 will commit sucide
    esp_task_wdt_init(1, true);
    esp_task_wdt_add(NULL);
    while (true)
      ;
  }
}

bool saveFACTORY()
{ // esp32
  DEBUG_Init("Saving FACTORY Settings");
  DynamicJsonDocument json(1024);
  json["host"] = hostFACTORY;
  json["ssid"] = ssidFACTORY;
  json["password"] = passwordFACTORY;
  json["AP_SSID"] = AP_SSIDFACTORY;
  json["AP_PASS"] = AP_PASSFACTORY;
  char cstr1[1];
  itoa(AP_HIDDENFACTORY, cstr1, 10);
  json["AP_HIDDEN"] = cstr1;
  json["mqtt_broker"] = mqtt_brokerFACTORY;
  char cstr2[8];
  itoa(mqtt_portFACTORY, cstr2, 10);
  json["mqtt_port"] = cstr2;
  json["mqtt_username"] = mqtt_usernameFACTORY;
  json["mqtt_password"] = mqtt_passwordFACTORY;
  char cstr3[1];
  itoa(darkStateFACTORY, cstr3, 10);
  json["darkState"] = cstr3;
  json["htmltitle"] = htmltitleFACTORY;
  json["htmltype"] = htmltypeFACTORY;
  json["htmlcolor"] = htmlcolorFACTORY;
  json["htmlhover"] = htmlhoverFACTORY;
  char cstr4[4];
  itoa(systemcurrentFACTORY, cstr4, 10);
  // json["systemcurrent"] = cstr4;
  char cstr5[4];
  itoa(portcurrent0FACTORY, cstr5, 10);
  // json["portcurrent0"] = cstr5;
  char cstr6[4];
  itoa(portcurrent1FACTORY, cstr6, 10);
  // json["portcurrent1"] = cstr6;
  char cstr7[4];
  itoa(portcurrent2FACTORY, cstr7, 10);
  // json["portcurrent2"] = cstr7;
  char cstr8[4];
  itoa(portcurrent3FACTORY, cstr8, 10);
  // json["portcurrent3"] = cstr8;
  char cstr9[1];
  itoa(overrideMODEFACTORY, cstr9, 10);
  json["overrideMODE"] = cstr9;
  char cstr11[1];
  itoa(overrideWEBFACTORY, cstr11, 10);
  json["overrideWEB"] = cstr11;
  char cstr12[3];
  itoa(brightnessFACTORY, cstr12, 10);
  json["brightness"] = cstr12;

  File configFile = LITTLEFS.open("/config.json", "w");
  if (!configFile)
  {
    DEBUG_Trouble("failed to open config file for writing - saveFACTORY");
    return false;
  }

  if (DEBUG_JSON)
  {
    serializeJson(json, Serial);
  }
  serializeJson(json, configFile);

  configFile.close();
  //end save
  DEBUG_Success("Saved FACTORY Settings - saveFACTORY");
  DEBUG_Separator();
  return true;
}

bool saveConfignew()
{ // esp32
  DEBUG_Init("saving NEW config");
  DynamicJsonDocument json(1024);
  json["host"] = host;
  json["ssid"] = ssid;
  json["password"] = password;
  json["AP_SSID"] = AP_SSID;
  json["AP_PASS"] = AP_PASS;
  char cstr1[1];
  itoa(AP_HIDDEN, cstr1, 10);
  json["AP_HIDDEN"] = cstr1;
  json["mqtt_broker"] = mqtt_broker;
  char cstr2[5];
  itoa(mqtt_port, cstr2, 10);
  json["mqtt_port"] = cstr2;
  json["mqtt_username"] = mqtt_username;
  json["mqtt_password"] = mqtt_password;
  char cstr3[1];
  itoa(darkState, cstr3, 10);
  json["darkState"] = cstr3;
  json["htmltitle"] = htmltitle;
  json["htmltype"] = htmltype;
  json["htmlcolor"] = htmlcolor;
  json["htmlhover"] = htmlhover;
  char cstr4[4];
  // itoa(systemcurrent, cstr4, 10);
  // json["systemcurrent"] = cstr4;
  char cstr5[4];
  // itoa(portcurrent0, cstr5, 10);
  // json["portcurrent0"] = cstr5;
  char cstr6[4];
  // itoa(portcurrent1, cstr6, 10);
  // json["portcurrent1"] = cstr6;
  char cstr7[4];
  // itoa(portcurrent2, cstr7, 10);
  // json["portcurrent2"] = cstr7;
  char cstr8[4];
  // itoa(portcurrent3, cstr8, 10);
  // json["portcurrent3"] = cstr8;
  char cstr9[1];
  itoa(overrideMODE, cstr9, 10);
  json["overrideMODE"] = cstr9;
  char cstr11[1];
  itoa(overrideWEB, cstr11, 10);
  json["overrideWEB"] = cstr11;
  char cstr12[3];
  itoa(brightness, cstr12, 10);
  json["brightness"] = cstr12;

  File configFile = LITTLEFS.open("/config.json", "w");
  if (!configFile)
  {
    DEBUG_Trouble("failed to open config file for writing - saveConfignew");
    return false;
  }

  if (DEBUG_JSON)
  {
    serializeJson(json, Serial);
  }
  serializeJson(json, configFile);

  configFile.close();
  DEBUG_Success("Saved NEW Settings - saveConfignew");
  DEBUG_Separator();
  return true;
}

bool loadConfig()
{ // LITTLEFS used for esp32
  DEBUG_Init("Config");
  if (LITTLEFS.exists("/config.json"))
  {
    //file exists, reading and loading
    DEBUG_Success("loadConfig: reading config file");
    File configFile = LITTLEFS.open("/config.json", "r");

    if (configFile)
    {
      DEBUG_Success("loadConfig: opened config file");
      size_t size = configFile.size();
      // Allocate a buffer to store contents of the file.
      std::unique_ptr<char[]> buf(new char[size]);

      configFile.readBytes(buf.get(), size);

      DynamicJsonDocument json(1024);
      auto deserializeError = deserializeJson(json, buf.get());
      if (DEBUG_JSON)
      {
        serializeJson(json, Serial);
      }
      if (!deserializeError)
      {

        strcpy(host, json["host"]);
        strcpy(ssid, json["ssid"]);
        strcpy(password, json["password"]);
        strcpy(AP_SSID, json["AP_SSID"]);
        strcpy(AP_PASS, json["AP_PASS"]);
        String convert1 = json["AP_HIDDEN"];
        AP_HIDDEN = convert1.toInt();
        strcpy(mqtt_broker, json["mqtt_broker"]);
        String convert2 = json["mqtt_port"];
        mqtt_port = convert2.toInt();
        strcpy(mqtt_username, json["mqtt_username"]);
        strcpy(mqtt_password, json["mqtt_password"]);
        String convert3 = json["darkState"];
        darkState = convert3.toInt();
        strcpy(htmltitle, json["htmltitle"]);
        strcpy(htmltype, json["htmltype"]);
        strcpy(htmlcolor, json["htmlcolor"]);
        strcpy(htmlhover, json["htmlhover"]);
        // String convert4 = json["systemcurrent"];
        // systemcurrent = convert4.toInt();
        // String convert5 = json["portcurrent0"];
        // portcurrent0 = convert5.toInt();
        // String convert6 = json["portcurrent1"];
        // portcurrent1 = convert6.toInt();
        // String convert7 = json["portcurrent2"];
        // portcurrent2 = convert7.toInt();
        // String convert8 = json["portcurrent3"];
        portcurrent3 = convert8.toInt();
        String convert9 = json["overrideMODE"];
        overrideMODE = convert9.toInt();
        String convert11 = json["overrideWEB"];
        overrideWEB = convert11.toInt();
        String convert12 = json["brightness"];
        brightness = convert12.toInt();
      }
      else
      {
        DEBUG_Trouble("loadConfig: failed to load json config");
        return false;
      }
      configFile.close();
      DEBUG_Success("loadConfig: file closed");
      return true;
    }
  }
  DEBUG_Trouble("loadConfig: config file doesn't exist");
  return false;
}
#endif

void parameterSETUP()
{
#if defined(ESP8266)
  if (!LittleFS.begin())
  {
    DEBUG_Trouble("parameterSETUP: Failed to mount file system");
    return;
  }
#elif defined(ESP32)
  if (!LITTLEFS.begin())
  {
    DEBUG_Trouble("parameterSETUP: Failed to mount file system");
    return;
  }
#endif
  else
  {
    if (!loadConfig())
    {
      DEBUG_Trouble("parameterSETUP: Failed to load Saved Config");
      DEBUG_Init("Saving Factory Information");
      saveFACTORY();
      delay(500);
      DEBUG_Success("parameterSETUP: Trying to read Factory Config");
      if (!loadConfig())
      {
        DEBUG_Trouble("parameterSETUP: Couldn't read Factory Config");
      }
      else
      {
        DEBUG_Success("parameterSETUP: Trying to read Factory Config");
      }
    }
    else
    {
      DEBUG_Success("parameterSETUP: Saved Config loaded");
      // DEBUG_Title(host, htmltype); // debug title screen
      // DEBUG_Title();

    }
  }
}

void wifisaving(AsyncWebServerRequest *request)
{
  DEBUG_Init("Website Config Save");
  String host_ = request->arg("host");
  if (host_ != NULL) // we have a value to do something with
  {
    if (host_ != host) // new color requested
    {
      strcpy(host, host_.c_str());
      new_update = true;
      restartRequired = true;
    }
  }

  String ssid_ = request->arg("ssid");
  if (ssid_ != NULL) // we have a value to do something with
  {
    if (ssid_ != ssid) // new color requested
    {
      strcpy(ssid, ssid_.c_str());
      new_update = true;
      restartRequired = true;
    }
  }

  String password_ = request->arg("password");
  if (password_ != NULL) // we have a value to do something with
  {
    if (password_ != password) // new color requested
    {
      strcpy(password, password_.c_str());
      new_update = true;
      restartRequired = true;
    }
  }

  String apssid_ = request->arg("apssid");
  if (apssid_ != NULL) // we have a value to do something with
  {
    if (apssid_ != AP_SSID) // new color requested
    {
      strcpy(AP_SSID, apssid_.c_str());
      new_update = true;
      restartRequired = true;
    }
  }

  String appass_ = request->arg("appass");
  if (appass_ != NULL) // we have a value to do something with
  {
    if (appass_ != AP_PASS) // new color requested
    {
      strcpy(AP_PASS, appass_.c_str());
      new_update = true;
      restartRequired = true;
    }
  }

  String hidden_ = request->arg("hidden");
  if (hidden_ != NULL) // we have a value to do something with
  {
    if (hidden_.toInt() != AP_HIDDEN) // new color requested
    {
      AP_HIDDEN = hidden_.toInt();
      new_update = true;
      restartRequired = true;
    }
  }

  String mqtt_ = request->arg("mqtt");
  if (mqtt_ != NULL) // we have a value to do something with
  {
    if (mqtt_ != mqtt_broker) // new color requested
    {
      strcpy(mqtt_broker, mqtt_.c_str());
      new_update = true;
      restartRequired = true;
    }
  }

  String port_ = request->arg("port");
  if (port_ != NULL) // we have a value to do something with
  {
    if (port_.toInt() != mqtt_port) // new color requested
    {
      mqtt_port = port_.toInt();
      new_update = true;
      restartRequired = true;
    }
  }

  String mqttuser_ = request->arg("mqttuser");
  if (mqttuser_ != NULL) // we have a value to do something with
  {
    if (mqttuser_ != mqtt_username) // new color requested
    {
      strcpy(mqtt_username, mqttuser_.c_str());
      new_update = true;
      restartRequired = true;
    }
  }

  String mqttpass_ = request->arg("mqttpass");
  if (mqttpass_ != NULL) // we have a value to do something with
  {
    if (mqttpass_ != mqtt_password) // new color requested
    {
      strcpy(mqtt_password, mqttpass_.c_str());
      new_update = true;
      restartRequired = true;
    }
  }

  String htmltitle_ = request->arg("htmltitle");
  if (htmltitle_ != NULL) // we have a value to do something with
  {
    if (htmltitle_ != htmltitle) // new color requested
    {
      strcpy(htmltitle, htmltitle_.c_str());
      new_update = true;
    }
  }

  String htmltype_ = request->arg("htmltype");
  if (htmltype_ != NULL) // we have a value to do something with
  {
    if (htmltype_ != htmltype) // new color requested
    {
      strcpy(htmltype, htmltype_.c_str());
      new_update = true;
    }
  }

  String dark_ = request->arg("dark");
  if (dark_ != NULL) // we have a value to do something with
  {
    if (dark_.toInt() != darkState) // new color requested
    {
      darkState = dark_.toInt();
      new_update = true;
    }
  }

  String htmlcolor_ = request->arg("htmlcolor");
  if (htmlcolor_ != NULL) // we have a value to do something with
  {
    if (htmlcolor_ != htmlcolor) // new color requested
    {
      strcpy(htmlcolor, htmlcolor_.c_str());
      new_update = true;
    }
  }

  String htmlhover_ = request->arg("htmlhover");
  if (htmlhover_ != NULL) // we have a value to do something with
  {
    if (htmlhover_ != htmlhover) // new color requested
    {
      strcpy(htmlhover, htmlhover_.c_str());
      new_update = true;
    }
  }

  String brightset_ = request->arg("brightset");
  if (brightset_ != NULL) // we have a value to do something with
  {
    if (brightset_.toInt() != brightness) // new color requested
    {
      if (brightset_.toInt() >= 0 && brightset_.toInt() <= 255)
      {
        for (int a = 0; a < 4; a++)
        {
          neo_update[a] = true;
        }
        brightness = brightset_.toInt();
        new_update = true;
      }
      else
      {
        DEBUG_Trouble("Brightness limited to 0-255 - change value");
      }
    }
  }

  if (new_update == true)
  { // we have new information to update
    DEBUG_Separator();
    saveConfignew();
  }
  else
  {
    DEBUG_Trouble("Nothing to save - wifisaving");
    DEBUG_Separator();
  }
}

// #endif // end of wifi save
