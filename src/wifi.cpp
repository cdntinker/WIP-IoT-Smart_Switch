/* Handles Wifi and AP mode - ON / OFF and timeout */

#include "LIBRARIES.h"

#include "wifi.h"
#include "EXTERNS.h"

extern char DEBUGtxt[92];

#include "neopixel.h"

uint8_t wifi_confirmed = false;
uint8_t ap_msg_timeout = false;
uint8_t ap_start = false;
uint8_t ap_connected = false; //returned from WiFi.softAPgetStationNum()
unsigned long prevAPmillis;
unsigned long wifimillis;
unsigned long timer;
unsigned long checkup;

void access_point_init()
{
  DEBUG_Init("Access Point");
  WiFi.softAPdisconnect(false);
  delay(200);
  //      WiFi.softAP(AP_SSID, AP_PASS);
  if (strcmp(AP_SSID, "0") == 0) // AP SSID hasn't been defined used host as our AP SSID
  {
    WiFi.softAP(host, AP_PASS, AP_CHANNEL, AP_HIDDEN, AP_MAX_CON);
    DEBUG_Wifi(host);
  }
  else
  {
    WiFi.softAP(AP_SSID, AP_PASS, AP_CHANNEL, AP_HIDDEN, AP_MAX_CON);
    DEBUG_Wifi(AP_SSID);
  }
  String APIPaddress = WiFi.softAPIP().toString();
  // DEBUG_IP(APIPaddress.c_str());
  DEBUG_IP();
  ap_start = true;
  DEBUG_Separator();
}

// start connecting to a WiFi network
void setup_wifi()
{
  WiFi.hostname(host);
  delay(10);
  /*BORK!*/DEBUG_Wifi(ssid);
  if (strcmp(password, "0") == 0) // non-password protected wifi
  {
    WiFi.begin(ssid);
  }
  else
  {
    WiFi.begin(ssid, password);
  }
  prevAPmillis = millis();
}

// check to see if we are connected to wifi
void wifi_checkup()
{
  if (millis() - checkup > 3000)
  {
    checkup = millis();
    if (WiFi.status() != WL_CONNECTED)
    {
      PIXELS_colorWipe(220, 0, 0, 0);
      wifi_confirmed = false;
      if (ap_start == false)
      {
        if (millis() - prevAPmillis > 30000) // start AP mode
        {
          DEBUG_Trouble("wifi not connecting - wifi_checkup");
          ap_msg_timeout = false;
          access_point_init(); // start AP for config
        }
      }
    }
    if (WiFi.status() == WL_CONNECTED)
    {
      if (wifi_confirmed == false)
      {
        DEBUG_Success("WiFi Connected");
        /*BORK!*/DEBUG_Wifi(ssid);
        String IPaddress1 = WiFi.localIP().toString();
        // DEBUG_IP(IPaddress1.c_str());
        DEBUG_IP();
        /*BORK!*/DEBUG_MAC(WiFi.macAddress().c_str());
        char rssi1[5];
        itoa(WiFi.RSSI(), rssi1, 10);
        char buf[12];
        sprintf(buf, "%s dBm", rssi1);
        DEBUG_rssi(buf);
        DEBUG_Separator();
        wifi_confirmed = true;
      }
      prevAPmillis = millis();

      if (ap_connected == false) // no one is connected to AP
      {
        if (ap_msg_timeout == false)
        {
          WiFi.softAPdisconnect(true);
          DEBUG_Separator();
          DEBUG_Success("AP mode disabled - wifi restored");
          DEBUG_Separator();
          ap_msg_timeout = true;
        }
      }
    }
    wifimillis = millis();

    // this works - shows number of stations connected to AP wifi - turns off ap when conencted to wifi - and no clients connected
    if ((millis() - timer) > 5000)
    {
      if (ap_start == true)
      {
        //  sprintf(DEBUGtxt, "Stations connected = %d\n", WiFi.softAPgetStationNum());
        //  DEBUG_LineOut(DEBUGtxt);

        ap_connected = WiFi.softAPgetStationNum();
      }
      timer = millis();
    }
  }
}

void wifi_start()
{
  WiFi.mode(WIFI_AP_STA);

  if (strcmp(ssid, "0") == 0)
  {
    DEBUG_Init("wifi not defined starting AP - wifi_start");
    access_point_init(); // start AP for config
  }
  else
  {
    //  DEBUG_LineOut(ssid);
    DEBUG_Init(" WiFi");
    setup_wifi(); // start regular wifi
  }
}
