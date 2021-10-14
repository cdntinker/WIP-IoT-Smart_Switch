/* Handles The ASYNC server webpages*/

// #include "LIBRARIES.h"
#include "EXTERNS.h"
#include "Tinker_DEBUG.h"

#include "DEVICE_SPECIFIC.h"

#include "wifisave.h"
#include "customserver.h"
#include "processing_items.h"

/* WEB PAGES */
#include "HTML_homepage.h"        // website home page
#include "HTML_management.h"      // Website OTA page
#include "HTML_config_page.h"     // ESP html configuration page
#include "HTML_failed.h"          // Something failed webpage
#include "HTML_reboot.h"          // Website - ESP rebooting
#include "HTML_finished.h"        // OTA success Webpage
#include "HTML_config_finished.h" // Saved Config Message Webpage
#include "HTML_factory.h"         // Factory Reset Performed Webpage

AsyncWebServer server(80); // declare ASYNC server library
AsyncWebSocket ws("/ws");  // declare web socket

const char *PARAM_INPUT_1 = "state";
// const char *PARAM_INPUT_2 = "RelayNum";
// const char *PARAM_INPUT_3 = "Action";
// const char *PARAM_INPUT_4 = "LEDNum";

extern char DEBUGtxt[92];

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *WSclient, AwsEventType type,
             void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        ws_connected++; // add to our connected websocket counted
        sprintf(DEBUGtxt, "WebSocket client #%u connected from %s", WSclient->id(), WSclient->remoteIP().toString().c_str());
        DEBUG_LineOut(DEBUGtxt);
        break;
    case WS_EVT_DISCONNECT:
        ws_connected--; // subtract from our websocket count
        sprintf(DEBUGtxt, "WebSocket client #%u disconnected", WSclient->id());
        DEBUG_LineOut(DEBUGtxt);
        break;
    case WS_EVT_DATA:
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}

void initWebSocket()
{
    ws.onEvent(onEvent);
    server.addHandler(&ws);
}

void OTA_Restart()
{
    yield();
    delay(250);
    yield();
#if defined(ESP8266)
    ESP.restart();
#elif defined(ESP32)
    // ESP32 will commit sucide
    esp_task_wdt_init(1, true);
    esp_task_wdt_add(NULL);
    while (true)
        ;
#endif
}

char CurrentPage[32];

boolean customInit()
{
    DEBUG_Init("ASYNC Server Starting");

    server.on("/pressed", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  if (request->hasParam(PARAM_ID))
                  {
                      String inputMessage1 = request->getParam(PARAM_ID)->value();
                      // sprintf(DEBUGtxt, "pressed : %s", inputMessage1);
                      // DEBUG_LineOut(DEBUGtxt);
                      //      WIFIbuttonSTATE[inputMessage1.toInt()] = LOW;
                  }
                  request->send(200, "text/plain", "OK");
              });

    server.on("/released", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  if (request->hasParam(PARAM_ID))
                  {
                      String inputMessage2 = request->getParam(PARAM_ID)->value();
                      // sprintf(DEBUGtxt, "Released : %s", inputMessage2);
                      // DEBUG_LineOut(DEBUGtxt);
                      //      WIFIbuttonSTATE[inputMessage2.toInt()] = HIGH;
                  }
                  request->send(200, "text/plain", "OK");
              });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->redirect("/home"); });
    DEBUG_LineOut("Page: /");

    server.on("/home", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  strcpy(CurrentPage, "/home"); // For button display from TinkerLibs-HTTP
                  request->send_P(200, "text/html", home_html, processor);
              });
    DEBUG_LineOut("Page: /home");

    server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  strcpy(CurrentPage, "/config"); // For button display from TinkerLibs-HTTP
                  request->send_P(200, "text/html", config_form, processor);
              });
    DEBUG_LineOut("Page: /config");

    server.on("/state", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  // sets online status
                  if (WiFi.status() != WL_CONNECTED)
                  {
                      request->send_P(200, "text/plain", "orange");
                  }
                  else
                  {
                      request->send_P(200, "text/plain", "green");
                  }
                  //    Serial.print("Received request from client with IP: ");         /////////////
                  //    Serial.println(request->WSclient()->remoteIP());                  /////////////
              });

    server.on("/management", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  strcpy(CurrentPage, "/management"); // For button display from TinkerLibs-HTTP
                  request->send_P(200, "text/html", management_html, processor);
              });
    DEBUG_LineOut("Page: /management");

    server.on("/complete", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->send_P(200, "text/html", finished_html, processor);
                  restartRequired = true;
              });

    server.on("/failedOTA", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  strcpy(CurrentPage, "/failedOTA"); // For button display from TinkerLibs-HTTP
                  request->send_P(200, "text/html", failed_html, processor);
              });

    server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->send_P(200, "text/html", reboot_html, processor);
                  restartRequired = true;
              });

    server.on("/factory", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  //     request->send_P(200, "text/html", reboot_html, processor );
                  request->redirect("/factorypage");
                  lastDelete = millis();
                  factoryRequired = true;
              });

    server.on("/factorypage", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  strcpy(CurrentPage, "/factorypage"); // For button display from TinkerLibs-HTTP
                  request->send_P(200, "text/html", factory_page, processor);
              });

    server.on("/wifisave", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  wifisaving(request);
                  request->send_P(200, "text/html", finished_config, processor);
                  //        restartRequired = true;
              });

    server.on("/darkmode", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  Serial.println("Dork Mode");
                  String inputMessage1;
                  if (request->hasParam(PARAM_INPUT_1))
                  {
                      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
                      if (inputMessage1 == "1")
                      {
                          darkState = !darkState;
                      }
                  }
                  request->send(200, "text/plain", "OK");
              });

    ///////////////////////////////////////////////////////////////////////////////////
    server.on("/RelayControl", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  String RLY_Num;
                  String RLY_Act;
                  DEBUG_SectionTitle("Web Input");
                  if (request->hasParam("RelayNum"))
                  {
                      RLY_Num = request->getParam("RelayNum")->value();
                  }
                  if (request->hasParam("Action"))
                  {
                      RLY_Act = request->getParam("Action")->value();
                      sprintf(DEBUGtxt, "Relay - #%ld, Action: %ld", RLY_Num.toInt(), RLY_Act.toInt());
                      DEBUG_LineOut(DEBUGtxt);
                      if (RLY_Act == "0")
                          DEVICE_RELAY(RLY_Num.toInt(), LOW); //   OFF
                      if (RLY_Act == "1")
                          DEVICE_RELAY(RLY_Num.toInt(), HIGH); //   ON
                      if (RLY_Act == "9")
                          DEVICE_RELAY_TOGGLE(RLY_Num.toInt()); //   TOGGLE
                  }
                  request->send(200, "text/plain", "OK");
              });

    server.on("/LEDControl", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  String LED_Num;
                  String LED_Act;
                  DEBUG_SectionTitle("Web Input");
                  if (request->hasParam("LEDNum"))
                  {
                      LED_Num = request->getParam("LEDNum")->value();
                  }
                  if (request->hasParam("Action"))
                  {
                      LED_Act = request->getParam("Action")->value();
                      sprintf(DEBUGtxt, "LED - #%ld, Action: %ld", LED_Num.toInt(), LED_Act.toInt());
                      DEBUG_LineOut(DEBUGtxt);
                      if (LED_Act == "0")
                          DEVICE_LED(LED_Num.toInt(), LOW); //   OFF
                      if (LED_Act == "1")
                          DEVICE_LED(LED_Num.toInt(), HIGH); //   ON
                      if (LED_Act == "9")
                          DEVICE_LED_TOGGLE(LED_Num.toInt()); //   TOGGLE
                  }
                  request->send(200, "text/plain", "OK");
              });
    ///////////////////////////////////////////////////////////////////////////////////

    server.on(
        "/management", HTTP_POST, [&](AsyncWebServerRequest *request)
        {
            // the request handler is triggered after the upload has finished...
            // create the response, add header, and send response
            //                 if (!_server->authenticate(_username.c_str(), _password.c_str())) {
            //                  return;
            //                 }
            AsyncWebServerResponse *response = request->beginResponse((Update.hasError()) ? 500 : 200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
            response->addHeader("Connection", "close");
            response->addHeader("Access-Control-Allow-Origin", "*");
            request->send(response);
            restartRequired = true;
        },
        [&](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
        {
            //Upload handler chunks in data

            if (!index)
            {

#if defined(ESP8266)
                int cmd = (filename == "filesystem") ? U_FS : U_FLASH;
                Update.runAsync(true);
                size_t fsSize = ((size_t)&_FS_end - (size_t)&_FS_start);
                uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
                if (!Update.begin((cmd == U_FS) ? fsSize : maxSketchSpace, cmd))
                { // Start with max available size
#elif defined(ESP32)
                int cmd = (filename == "filesystem") ? U_SPIFFS : U_FLASH;
                if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd))
                { // Start with max available size
#endif
                    Update.printError(Serial);
                    return request->send(400, "text/plain", "OTA could not begin");
                }
            }

            // Write chunked data to the free sketch space
            if (len)
            {
                if (Update.write(data, len) != len)
                {
                    return request->send(400, "text/plain", "OTA could not begin");
                }
            }

            if (final)
            { // if the final flag is set then this is the last frame of data
                if (!Update.end(true))
                { //true to set the size to the current progress
                    Update.printError(Serial);
                    return request->send(400, "text/plain", "Could not end OTA");
                }
            }
            else
            {
                return;
            }
        });

    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->send(404); });
    server.begin();
    DEBUG_Success("ASYNC Server Started - customInit");
    // DEBUG_Separator();
    return true;
}

void WEB_cleanupClients()
{
    ws.cleanupClients(); // cleans up old websocket clients
}

void WEB_textAll(String buf)
{
    ws.textAll(buf); // send the data
}
