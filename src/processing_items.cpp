/* This page and fuctions handle filling in %variables% in HTML webpages*/

// #ifndef processing_items_h
// #define processing_items_h

#include "LIBRARIES.h"
#include "EXTERNS.h"
#include "DEFINES.h"

#include "Tinker_DEBUG.h"
extern char DEBUGtxt[92];

#include "HTML_css.h"
#include "HTML_SCRIPTS.h"
#include "HTML_SCRIPTS_2.h"
// #include "HTML_SCRIPTS_3.h"

/* Internal blocks of HTML */
#include "HTML_PART_Header.h"
#include "HTML_PART_DeviceInfo.h"
#include "HTML_PART_Footer.h"
#include "HTML_PART_Status.h"
#include "HTML_PART_Battery.h"

#include "DEVICE_HTML_PART_Homepage.h"

#ifndef PART_HomePage_Body_h
#include "HTML_PART_HomeDefault.h"
#endif

/* Sections for the config page */
#include "HTML_PART_WiFi_Config.h"
#include "HTML_PART_AP_Config.h"
#include "HTML_PART_MQTT_Config.h"
#include "HTML_PART_WEB_UI_Config.h"
#include "HTML_PART_LEDs_Config.h"
// #include "HTML_PART_SmartHUB_Config.h"

// /**********************************************************************/
// /* Part of the button display from TinkerLibs-HTTP                    */
// /**********************************************************************/
struct PageMap
{
  bool IsAButton;       // Display this Button?
  char PageAddress[32]; // The page this button refers to...
  char PageLabel[32];   // The label on the button
  char ButtonClick[32]; // What happens when ya click this button
};

PageMap PageList[] =
    {
        {true, "/home", "Home", "location.href="},
        {true, "/management", "Management", "location.href="},
        {true, "/config", "Config", "location.href="},
        {false, "", "Dark Mode", "darkFunction()"},
        {false, "/factorypage", "RESET", "location.href="},
        {false, "/failedOTA", "FAIL", "location.href="},
};
int NumberofButtons = sizeof(PageList) / sizeof(PageList[0]);
extern char CurrentPage[32];

PageMap OTOListRLY[] =
    {
        {true, "", "ON", "RelayON"},
        {true, "", "Toggle", "RelayTOGGLE"},
        {true, "", "OFF", "RelayOFF"},
};
int NumberofStatesRLY = sizeof(OTOListRLY) / sizeof(OTOListRLY[0]);
char OTOstateRLY[32];

PageMap OTOListLED[] =
    {
        {true, "", "ON", "LEDON"},
        {true, "", "Toggle", "LEDTOGGLE"},
        {true, "", "OFF", "LEDOFF"},
};
int NumberofStatesLED = sizeof(OTOListLED) / sizeof(OTOListLED[0]);
char OTOstateLED[32];

// /**********************************************************************/

uint8_t deviceREBOOTED = true;

#if defined(ESP8266)
#elif defined(ESP32)
#include <rom/rtc.h>

String return_reset_reason(RESET_REASON reason)
{
  switch (reason)
  {
  case 1:
    return ("POWERON_RESET");
    break; /**<1, Vbat power on reset*/
  case 3:
    return ("SW_RESET");
    break; /**<3, Software reset digital core*/
  case 4:
    return ("OWDT_RESET");
    break; /**<4, Legacy watch dog reset digital core*/
  case 5:
    return ("DEEPSLEEP_RESET");
    break; /**<5, Deep Sleep reset digital core*/
  case 6:
    return ("SDIO_RESET");
    break; /**<6, Reset by SLC module, reset digital core*/
  case 7:
    return ("TG0WDT_SYS_RESET");
    break; /**<7, Timer Group0 Watch dog reset digital core*/
  case 8:
    return ("TG1WDT_SYS_RESET");
    break; /**<8, Timer Group1 Watch dog reset digital core*/
  case 9:
    return ("RTCWDT_SYS_RESET");
    break; /**<9, RTC Watch dog Reset digital core*/
  case 10:
    return ("INTRUSION_RESET");
    break; /**<10, Instrusion tested to reset CPU*/
  case 11:
    return ("TGWDT_CPU_RESET");
    break; /**<11, Time Group reset CPU*/
  case 12:
    return ("SW_CPU_RESET");
    break; /**<12, Software reset CPU*/
  case 13:
    return ("RTCWDT_CPU_RESET");
    break; /**<13, RTC Watch dog Reset CPU*/
  case 14:
    return ("EXT_CPU_RESET");
    break; /**<14, for APP CPU, reseted by PRO CPU*/
  case 15:
    return ("RTCWDT_BROWN_OUT_RESET");
    break; /**<15, Reset when the vdd voltage is not stable*/
  case 16:
    return ("RTCWDT_RTC_RESET");
    break; /**<16, RTC Watch dog reset digital core and rtc module*/
  default:
    return ("NO_MEAN");
  }
}
#endif

String DeviceID()
{
  // #if defined(DeviceName)
  //   String id = STR(DeviceName);
  // #else
  String id = host;
  // #endif
  return id;
}

// String info_memsketch()
// {
//   String memsketch = ((String)(ESP.getSketchSize())) + " / " + ((String)(ESP.getSketchSize() + ESP.getFreeSketchSpace())) + "  Used / Total";
//   return memsketch;
// }

String info_memsketch()
{
  int Size = ESP.getSketchSize();
  int Free = ESP.getFreeSketchSpace();
  int Flash = ESP.getFlashChipSize();
  // struct FSInfo {
  //     size_t totalBytes;
  //     size_t usedBytes;
  //     size_t blockSize;
  //     size_t pageSize;
  //     size_t maxOpenFiles;
  //     size_t maxPathLength;
  // };
  FSInfo fs_info;
  LittleFS.info(fs_info);

  String memsketch =
      ((String)(Flash / 1024)) +
      "k / " +
      ((String)(Size / 1024)) +
      "k / " +
      ((String)(Free / 1024)) +
      "k / " +
      ((String)(fs_info.totalBytes / 1024)) +
      "k<br>(Flash / Sketch / Free / FS)";
  return memsketch;
}

String ip3string(IPAddress ip)
{
  String ret = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
  return ret;
}

// ADC_MODE(ADC_VCC);   // If using SYSvoltage

String processor(const String &var)
{ // Change placeholders on webpage

  // if (var == "SYSvoltage")
  // {
  //   String battvolt = "";
  //   battvolt += ESP.getVcc();
  //   return battvolt;
  // }

// This is based on connecting a typical lithium single cell 
// to A0 of a D1-mini through a 220k resistor
// OR
// a ~1:5 divider (100K:470K) across the battery to ADC on an ESP-07-Everything!
  if (var == "BATTERYv")
  {
    String battvolt = "";
    battvolt += (analogRead(A0) / BATTDIV);     // ESP-Everything
    return battvolt;
  }

  if (var == "ADC")
  {
    String ADCreading = "";
    ADCreading += analogRead(A0);
    return ADCreading;
  }

  if (var == "battColor")
  {

    float Volts = analogRead(A0) / BATTDIV; // ESP-Everything

    if (Volts >= 3.7)
    {
      return "green";
    }
    else if (Volts >= 3.2)
    {
      return "orange";
    }
    else if (Volts >= 3.0)
    {
      return "red";
    }
    else
    {
      return "black";
    }
  }

  /* Drag in complete blocks of HTML */
  if (var == "PART_Header")
    return PART_Header_html;
  if (var == "PART_DeviceInfo")
    return PART_deviceinfo_html;

  if (var == "deviceinfo_WiFi")
    return PART_deviceinfo_WiFi_html;
  if (var == "deviceinfo_MQTT")
    return PART_deviceinfo_MQTT_html;
  if (var == "deviceinfo_Batt")
    return PART_deviceinfo_Batt_html;
  if (var == "deviceinfo_Mem")
    return PART_deviceinfo_Mem_html;
  if (var == "deviceinfo_Firm")
    return PART_deviceinfo_Firm_html;

  if (var == "PART_Footer")
    return PART_Footer_html;
  if (var == "PART_status")
    return PART_status_html;
  if (var == "PART_battery")
    return PART_battery_html;
  if (var == "The_CSS")
    return CSS_STYLE;
  if (var == "The_SCRIPTS")
    return CSS_SCRIPTS;
  if (var == "More_SCRIPTS")
    return CSS_SCRIPTS2;
  // if (var == "Yet_More_SCRIPTS")
  //   return CSS_SCRIPTS3;
  if (var == "PART_HomePage_Body")
    return PART_HomePage_Body;

 if (var == "PART_HomePage_Body_Relays")
    return PART_HomePage_Body_Relays;
 if (var == "PART_HomePage_Body_LEDs")
    return PART_HomePage_Body_LEDs;
 if (var == "PART_HomePage_Body_Buttons")
    return PART_HomePage_Body_Buttons;
 if (var == "PART_HomePage_Body_Inputs_direct")
    return PART_HomePage_Body_Inputs_direct;
 if (var == "PART_HomePage_Body_Inputs_sensors")
    return PART_HomePage_Body_Inputs_sensors;


  if (var == "config_form_WiFi")
    return config_form_WiFi;
  if (var == "config_form_AP")
    return config_form_AP;
  if (var == "config_form_MQTT")
    return config_form_MQTT;
  if (var == "config_form_WEB_UI")
    return config_form_WEB_UI;
  if (var == "config_form_LEDs")
    return config_form_LEDs;

  /* Button Styles */

  /**********************************************************************/
  /* The Header Menu Buttons                                            */
  /**********************************************************************/
  if (var == "ALLDAButtons")
  {

    String TheHTML = "<div class = \"menu-buttons\">";
    char TheButtons[1024];
    String ButtonClass;

    for (int PageListCTR = 0; PageListCTR < NumberofButtons; PageListCTR++)
    {
      if (!strcmp(PageList[PageListCTR].PageAddress, CurrentPage))
        ButtonClass = "ButtonHere";
      else
        ButtonClass = "ButtonClickable";

      String ClickAction = PageList[PageListCTR].ButtonClick;

      if (strlen(PageList[PageListCTR].PageAddress) != 0)
      {
        ClickAction += "'";
        ClickAction += PageList[PageListCTR].PageAddress;
        ClickAction += "'";
      }
      if (PageList[PageListCTR].IsAButton)
      {
        sprintf(TheButtons,
                "<div class = \"buttons %s\"> <button%d onclick=\"%s\">%s</button%d> </div>\n",
                ButtonClass.c_str(),
                PageListCTR,
                ClickAction.c_str(),
                PageList[PageListCTR].PageLabel,
                PageListCTR);
        TheHTML += TheButtons;
      }
    }
    TheHTML += "</DIV>";

    return TheHTML;
  }
  /**********************************************************************/

  /**********************************************************************/
  /* On / Toggle / Off Buttons                                          */
  /* And input indicators                                               */
  /**********************************************************************/

  extern int GPIO_Relay_PINS[4];
  extern bool GPIO_Relay_STATE[4];
  extern int GPIO_Relay_COUNT;

  extern int GPIO_LED_PINS[4];
  extern bool GPIO_LED_STATE[4];
  extern int GPIO_LED_COUNT;

  extern unsigned int GPIO_Button_PINS[4];  //WTFdude
  extern bool GPIO_Button_STATE[4];
  extern int GPIO_Button_COUNT;

  if (var.startsWith("OTOoutputs"))
  {
    DEBUG_SectionTitle(var.c_str());

    char WTF[50];
    var.toCharArray(WTF, 50);
    char *Token = NULL;
    Token = strtok(WTF, ".");
    // Serial.println(Token);
    Token = strtok(NULL, ".");
    // Serial.println(Token); // This is the TYPE of device

    // int GPIO_Pin[4];
    // bool GPIO_State[4];
    // int GPIO_Count;

    String TheHTML = "<div class = \"menu-buttons\">";

    if (strcmp(Token, "Relays") == 0)
    {

      // Serial.printf("GPIO_Relay_COUNT: %d\n", GPIO_Relay_COUNT);

      for (int DeviceCTR = 0; DeviceCTR < GPIO_Relay_COUNT; DeviceCTR++)
      {

        // Serial.printf("DeviceCTR: %d\n", DeviceCTR);

        sprintf(DEBUGtxt, "Button Group > %2d", DeviceCTR);
        DEBUG_LineOut(DEBUGtxt);
        String GroupNumber = String(DeviceCTR);
        String TheLabel = "<font size=\"+1\"><b>Relay #";
        TheLabel += DeviceCTR;
        TheLabel += "</b></font>\n";
        TheHTML += TheLabel;

        if (GPIO_Relay_STATE[DeviceCTR])
          strcpy(OTOstateRLY, "ON");
        else
          strcpy(OTOstateRLY, "OFF");

        char TheButtons[1024];
        String ButtonClass;

        for (int OTOListCTR = 0; OTOListCTR < NumberofStatesRLY; OTOListCTR++)
        {
          if (!strcmp(OTOListRLY[OTOListCTR].PageLabel, OTOstateRLY)) // GPIO_Relay_STATE[0]
            ButtonClass = "ButtonHere";
          else
            ButtonClass = "ButtonClickable";

          String ClickAction = OTOListRLY[OTOListCTR].ButtonClick;

          if (strlen(OTOListRLY[OTOListCTR].PageAddress) != 0)
          {
            ClickAction += "'";
            ClickAction += OTOListRLY[OTOListCTR].PageAddress;
            ClickAction += "'";
          }
          else
          {
            ClickAction += "(";
            ClickAction += GroupNumber;
            ClickAction += ")";
          }
          if (OTOListRLY[OTOListCTR].IsAButton)
          {

            // sprintf(DEBUGtxt, "Button > %s", ClickAction.c_str());
            // DEBUG_LineOut2(DEBUGtxt);

            sprintf(TheButtons,
                    "<div class = \"buttons %s\"> <button%d onclick=\"%s\">%s</button%d> </div>\n",
                    ButtonClass.c_str(),
                    OTOListCTR,
                    ClickAction.c_str(),
                    OTOListRLY[OTOListCTR].PageLabel,
                    OTOListCTR);
            TheHTML += TheButtons;
          }
        }
        TheHTML += "<font size=\"1\"> (io ";
        TheHTML += GPIO_Relay_PINS[DeviceCTR];
        TheHTML += ")</font>";
        TheHTML += "<br>\n";
      }
    }
    else if (strcmp(Token, "LEDs") == 0)
    {

      // Serial.printf("GPIO_LED_COUNT: %d\n", GPIO_LED_COUNT);

      for (int DeviceCTR = 0; DeviceCTR < GPIO_LED_COUNT; DeviceCTR++)
      {

        // Serial.printf("DeviceCTR: %d\n", DeviceCTR);

        sprintf(DEBUGtxt, "Button Group > %2d", DeviceCTR);
        DEBUG_LineOut(DEBUGtxt);
        String GroupNumber = String(DeviceCTR);
        String TheLabel = "<font size=\"+1\"><b>LED #";
        TheLabel += DeviceCTR;
        TheLabel += "</b></font>\n";
        TheHTML += TheLabel;

        if (GPIO_LED_STATE[DeviceCTR])
          strcpy(OTOstateLED, "ON");
        else
          strcpy(OTOstateLED, "OFF");

        char TheButtons[1024];
        String ButtonClass;

        for (int OTOListCTR = 0; OTOListCTR < NumberofStatesLED; OTOListCTR++)
        {
          if (!strcmp(OTOListLED[OTOListCTR].PageLabel, OTOstateLED)) // SmartSwitch_LED_STATE[0]
            ButtonClass = "ButtonHere";
          else
            ButtonClass = "ButtonClickable";

          String ClickAction = OTOListLED[OTOListCTR].ButtonClick;

          if (strlen(OTOListLED[OTOListCTR].PageAddress) != 0)
          {
            ClickAction += "'";
            ClickAction += OTOListLED[OTOListCTR].PageAddress;
            ClickAction += "'";
          }
          else
          {
            ClickAction += "(";
            ClickAction += GroupNumber;
            ClickAction += ")";
          }
          if (OTOListLED[OTOListCTR].IsAButton)
          {

            // sprintf(DEBUGtxt, "Button > %s", ClickAction.c_str());
            // DEBUG_LineOut2(DEBUGtxt);

            sprintf(TheButtons,
                    "<div class = \"buttons %s\"> <button%d onclick=\"%s\">%s</button%d> </div>\n",
                    ButtonClass.c_str(),
                    OTOListCTR,
                    ClickAction.c_str(),
                    OTOListLED[OTOListCTR].PageLabel,
                    OTOListCTR);
            TheHTML += TheButtons;
          }
        }
        TheHTML += "<font size=\"1\"> (io ";
        TheHTML += GPIO_LED_PINS[DeviceCTR];
        TheHTML += ")</font>";
        TheHTML += "<br>\n";
      }
    }
    TheHTML += "</DIV>";
    return TheHTML;
  }

  if (var.startsWith("OTOInputs"))
  {
    DEBUG_SectionTitle(var.c_str());

    char WTF[50];
    var.toCharArray(WTF, 50);
    char *Token = NULL;
    Token = strtok(WTF, ".");
    // Serial.println(Token);
    Token = strtok(NULL, ".");
    // Serial.println(Token); // This is the TYPE of device

    // int GPIO_Pin[4];
    // bool GPIO_State[4];
    // int GPIO_Count;

    String TheHTML = "<div class = \"menu-buttons\">";

    if (strcmp(Token, "Buttons") == 0)
    {
      for (int DeviceCTR = 0; DeviceCTR < GPIO_Button_COUNT; DeviceCTR++)
      {
        sprintf(DEBUGtxt, "Button Group > %2d", DeviceCTR);
        DEBUG_LineOut(DEBUGtxt);
        String GroupNumber = String(DeviceCTR);
        String TheLabel = "<font size=\"+1\"><b>Button #";
        TheLabel += DeviceCTR;
        TheLabel += "</b></font>\n";
        TheHTML += TheLabel;

        if (GPIO_Button_STATE[DeviceCTR])
          strcpy(OTOstateRLY, "ON");
        else
          strcpy(OTOstateRLY, "OFF");

        char TheButtons[1024];
        String ButtonClass;

        for (int OTOListCTR = 0; OTOListCTR < NumberofStatesRLY; OTOListCTR++)
        {
          if (!strcmp(OTOListRLY[OTOListCTR].PageLabel, OTOstateRLY)) // GPIO_Button_STATE[0]
            ButtonClass = "ButtonHere";
          else
            ButtonClass = "ButtonClickable";

          String ClickAction = OTOListRLY[OTOListCTR].ButtonClick;

          if (strlen(OTOListRLY[OTOListCTR].PageAddress) != 0)
          {
            ClickAction += "'";
            ClickAction += OTOListRLY[OTOListCTR].PageAddress;
            ClickAction += "'";
          }
          else
          {
            ClickAction += "(";
            ClickAction += GroupNumber;
            ClickAction += ")";
          }
          if (OTOListRLY[OTOListCTR].IsAButton)
          {

            // sprintf(DEBUGtxt, "Button > %s", ClickAction.c_str());
            // DEBUG_LineOut2(DEBUGtxt);

            sprintf(TheButtons,
                    "<div class = \"buttons %s\"> <button%d onclick=\"%s\">%s</button%d> </div>\n",
                    ButtonClass.c_str(),
                    OTOListCTR,
                    ClickAction.c_str(),
                    OTOListRLY[OTOListCTR].PageLabel,
                    OTOListCTR);
            TheHTML += TheButtons;
          }
        }
        TheHTML += "<font size=\"1\"> (io ";
        TheHTML += GPIO_Button_PINS[DeviceCTR];
        TheHTML += ")</font>";
        TheHTML += "<br>\n";
      }
    }
    else if (strcmp(Token, "Inputs") == 0)
    {
    }
    TheHTML += "</DIV>";
    return TheHTML;
  }

  /**********************************************************************/

  if (var == "dark")
  {
    if (darkState == false)
      return "body { background-color: white; color: black; }";
    else
      return "body { background-color: black; color: white; }";
  }

  if (var == "online")
  {
    if (WiFi.status() == WL_CONNECTED)
      return "background:green";
    else
      return "background:orange";
  }

  if (var == "title")
    return htmltitle;

  if (var == "PageName")
    for (int PageListCTR = 0; PageListCTR < NumberofButtons; PageListCTR++)
      if (!strcmp(PageList[PageListCTR].PageAddress, CurrentPage))
        return PageList[PageListCTR].PageLabel;

  if (var == "color")
    return htmlcolor;

  if (var == "hover")
    return htmlhover;

  if (var == "ssidplaceholder")
  {
    char rssi1[5];
    itoa(WiFi.RSSI(), rssi1, 10);
    // char buf[12];
    char buf[44];
    sprintf(buf, "%s (%s dBm)", ssid, rssi1);
    return buf;
  }

  if (var == "ipplaceholder")
    return ip3string(WiFi.localIP());

  if (var == "macplaceholder")
    return WiFi.macAddress();

  if (var == "brokerplaceholder")
    return mqtt_broker;

  if (var == "clientplaceholder")
    return DeviceID();

  if (var == "memsketch")
    return info_memsketch();

  if (var == "FirmwareVer")
    return STR(FIRMWAREVERSION);

  if (var == "DevName")
    return STR(DeviceName);

  if (var == "IDplaceholder")
    return DeviceID();

  if (var == "processorplaceholder")
  {
#if defined(ESP8266)
    return "ESP8266";
#elif defined(ESP32)
    return "ESP32";
#endif
  }

  if (var == "type")
    return STR(DeviceType);

  /* CONFIG Stuff */
  if (var == "IDfactory")
  {
    return hostFACTORY;
  }

  if (var == "IDssid") // filling in the config page with ssid if configured
  {
    String ssing = "";
    if (strcmp(ssid, "0") == 0)
    {
      ssing += "ssid";
      return ssing;
    }
    else
    {
      ssing += "ssid = ";
      ssing += ssid;
      return ssing;
    }
  }

  if (var == "whatpass") // filling in the config page with ssid password
  {
    String whatping = "";
    if (strcmp(password, "0") == 0)
    {
      whatping += "WiFi password";
      return whatping;
    }
    else
    {
      whatping += "Password Set";
      return whatping;
    }
  }

  if (var == "passwhat") // filling in the config page ap password
  {
    String whatsping = "";
    whatsping += "Password Set";
    return whatsping;
  }

  if (var == "apss") // filling in the config page ap ssid
  {
    String apssing = "";
    apssing += "AP SSID = ";
    apssing += AP_SSID;
    return apssing;
  }

  if (var == "aphid") // filling in the config page ap hidden value
  {
    String aphing = "";
    aphing += "AP hidden = ";
    aphing += AP_HIDDEN;
    return aphing;
  }

  if (var == "broker") // filling in the config page with broker if configured
  {
    String brokeing = "";
    if (strcmp(mqtt_broker, "0") == 0)
    {
      brokeing += "mqtt broker";
      return brokeing;
    }
    else
    {
      brokeing += "mqtt broker = ";
      brokeing += mqtt_broker;
      return brokeing;
    }
  }

  if (var == "port") // filling in the config page with port if configured
  {
    String porting = "";
    porting += "port = ";
    porting += mqtt_port;
    return porting;
  }

  if (var == "userID") // filling in the config page with userID if configured
  {
    String ming = "";
    if (strcmp(mqtt_username, "0") == 0)
    {
      ming += "mqtt username";
      return ming;
    }
    else
    {
      ming += "mqtt username = ";
      ming += mqtt_username;
      return ming;
    }
  }

  if (var == "notpass") // filling in the config page with mqtt password if configured
  {
    String mping = "";
    if (strcmp(mqtt_password, "0") == 0)
    {
      mping += "mqtt password";
      return mping;
    }
    else
    {
      mping += "Password Set";
      return mping;
    }
  }

  if (var == "darkmode") // filling in the config page darkmode value
  {
    String dming = "";
    dming += "Dark Mode = ";
    dming += darkState;
    return dming;
  }

  if (var == "currentsys") // filling in the config page
  {
    String dm1ing = "";
    dm1ing += "System Current = ";
    // dm1ing += systemcurrent;
    return dm1ing;
  }

  if (var == "current1") // filling in the config page
  {
    String dm2ing = "";
    dm2ing += "Port 1 Current = ";
    // dm2ing += portcurrent0;
    return dm2ing;
  }

  if (var == "current2") // filling in the config page
  {
    String dm3ing = "";
    dm3ing += "Port 2 Current = ";
    // dm3ing += portcurrent1;
    return dm3ing;
  }

  if (var == "current3") // filling in the config page
  {
    String dm4ing = "";
    dm4ing += "Port 3 Current = ";
    // dm4ing += portcurrent2;
    return dm4ing;
  }

  if (var == "current4") // filling in the config page
  {
    String dm5ing = "";
    dm5ing += "Port 4 Current = ";
    // dm5ing += portcurrent3;
    return dm5ing;
  }

  if (var == "brightsys") // filling in the config page
  {
    String dm6ing = "";
    dm6ing += "LED Brightness = ";
    dm6ing += brightness;
    return dm6ing;
  }

  // if (var == "modeover2") // filling in the config page ap overrideMODE value
  // {
  //   String dm7ing = "";
  //   dm7ing += "overrideMODE = ";
  //   dm7ing += overrideMODE;
  //   return dm7ing;
  // }

  if (var == "wifiover") // filling in the config page ap overrideWIFI value
  {
    String dm8ing = "";
    dm8ing += "overrideWIFI = ";
    // dm8ing += overrideWEB;
    return dm8ing;
  }

  if (var == "errorplaceholder")
  {
    String erroring = "";
    if (deviceREBOOTED == false)
    {
      erroring += "";
    }
    else
    {
      erroring += "Device Rebooted";
      deviceREBOOTED = false;
      erroring += " (";

#if defined(ESP8266)
      String RebootReason =
          ESP.getResetReason().c_str();
#elif defined(ESP32)
      String RebootReason =
          return_reset_reason(rtc_get_reset_reason(0));
      erroring += RebootReason;
      erroring += "/";
      RebootReason =
          return_reset_reason(rtc_get_reset_reason(1));
#endif
      erroring += RebootReason;
      erroring += ")";
    }
    return erroring;
  }

  return String();
}

// #endif
