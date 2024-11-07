/* DeviceInfo HTML */ 

#ifndef HTML_PART_DeviceInfo_h
#define HTML_PART_DeviceInfo_h

const char PART_deviceinfo_html[] PROGMEM = R"rawliteral(
<div class = "border">
  <div class = "row">
%deviceinfo_WiFi%
%deviceinfo_MQTT%
%deviceinfo_Batt%
%deviceinfo_Mem%
%deviceinfo_Firm%
  </div>
</div>
)rawliteral";

const char PART_deviceinfo_WiFi_html[] PROGMEM = R"rawliteral(
    <div class = "innerl">
      <div class = "column1">
        <div class = "name-text">SSID: </div>
        <div class = "name-text">IP Address: </div>
        <div class = "name-text">MAC Address: </div>
      </div>
    </div>
    
    <div class = "innerr">
      <div class = "column2">
        <div class = "host-text">%ssidplaceholder%</div>
        <div class = "host-text">%ipplaceholder%</div>
        <div class = "host-text">%macplaceholder%</div>
      </div>
    </div>
)rawliteral";

const char PART_deviceinfo_MQTT_html[] PROGMEM = R"rawliteral(
    <div class = "innerl">
      <div class = "column1">
        <div class = "name-text">MQTT Broker: </div>
        <div class = "name-text">MQTT Client: </div>
      </div>
    </div>
    
    <div class = "innerr">
      <div class = "column2">
        <div class = "host-text">%brokerplaceholder%</div>
        <div class = "host-text">%clientplaceholder%</div>
      </div>
    </div>
)rawliteral";

#ifdef SmartSwitch_ADC
const char PART_deviceinfo_Batt_html[] PROGMEM = R"rawliteral(
    <div class = "innerl">
      <div class = "column1">
        <div class = "name-text">Battery: </div>
      </div>
    </div>
    
    <div class = "innerr">
      <div class = "column2">
        <div class = "host-text">%BATTERYv%V (ADC: %ADC%)</div>
      </div>
    </div>
)rawliteral";
#else
const char PART_deviceinfo_Batt_html[] PROGMEM = R"rawliteral(
)rawliteral";
#endif

const char PART_deviceinfo_Mem_html[] PROGMEM = R"rawliteral(
    <div class = "innerl">
      <div class = "column1">
        <div class = "name-text">Flash Usage: </div>
        <br>
      </div>
    </div>
    
    <div class = "innerr">
      <div class = "column2">
        <div class = "host-text">%memsketch%</div>
      </div>
    </div>
)rawliteral";

const char PART_deviceinfo_Firm_html[] PROGMEM = R"rawliteral(
    <div class = "innerl">
      <div class = "column1">
        <div class = "name-text">Firmware Version: </div>
      </div>
    </div>
    
    <div class = "innerr">
      <div class = "column2">
        <div class = "host-text">%DevName% (%FirmwareVer%)</div>
      </div>
    </div>
)rawliteral";

#endif  // HTML_PART_DeviceInfo_h