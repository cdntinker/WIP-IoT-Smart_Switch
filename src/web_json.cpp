
// #ifndef web_json_h
// #define web_json_h

#include "LIBRARIES.h"
#include "EXTERNS.h"

#include "ESP_Color.h"
#include "customserver.h"

void webSENDjson()
{
      //  DEBUG_LineOut("[WSc] SENT: Broadcast message!!");   // debug
  const size_t capacity = 1024;
  DynamicJsonDocument doc(capacity);

  {
    doc["border0"] = "#422a2a";
    doc["port0"] = "red";
    doc["volt0"] = "----"; // no volts to calculate
    doc["voltstyle0"] = "red";
    doc["mastyle0"] = "red"; // current state - show red in lockout
    doc["ma0"] = "----";     // no power to calculate
    doc["p0"] = "DISABLE";   // power is disabled
    doc["d0"] = "DISABLE";   // data is disabled
  }

  {
    doc["border1"] = "#422a2a";
    doc["port1"] = "red";
    doc["volt1"] = "----"; // no volts to calculate
    doc["voltstyle1"] = "red";
    doc["mastyle1"] = "red"; // current state - show red in lockout
    doc["ma1"] = "----";     // no power to calculate
    doc["p1"] = "DISABLE";   // power is disabled
    doc["d1"] = "DISABLE";   // data is disabled
  }

  {
    doc["border2"] = "#422a2a";
    doc["port2"] = "red";
    doc["volt2"] = "----"; // no volts to calculate
    doc["voltstyle2"] = "red";
    doc["mastyle2"] = "red"; // current state - show red in lockout
    doc["ma2"] = "----";     // no power to calculate
    doc["p2"] = "DISABLE";   // power is disabled
    doc["d2"] = "DISABLE";   // data is disabled
  }

  {
    doc["border3"] = "#422a2a";
    doc["port3"] = "red";
    doc["volt3"] = "----"; // no volts to calculate
    doc["voltstyle3"] = "red";
    doc["mastyle3"] = "red"; // current state - show red in lockout
    doc["ma3"] = "----";     // no power to calculate
    doc["p3"] = "DISABLE";   // power is disabled
    doc["d3"] = "DISABLE";   // data is disabled
  }

  String buf;
  serializeJson(doc, buf); // package the data

  // ws.textAll(buf);       // send the data
  WEB_textAll(buf);
  lastUpdate = millis(); // last data update
}
// #endif
