#include <Arduino.h>

#include "FS.h"

#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>

#if defined(ESP8266)
    #include "ESP8266WiFi.h"
    #include "ESPAsyncTCP.h"
    #include "flash_hal.h"
    #include <LittleFS.h>

#elif defined(ESP32)
    #include "WiFi.h"
    #include "AsyncTCP.h"
    #include "Update.h"
    #include "esp_int_wdt.h"
    #include "esp_task_wdt.h"
    #include "LITTLEFS.h"
#endif

// #include <Adafruit_MCP23008.h>  // For Output Enables
// #include <Adafruit_INA219.h>    // For Current Measurements
#include <Adafruit_NeoPixel.h>  // for SK6812 RGBW LEDs

#include "Tinker_DEBUG.h" // embeded degug library
