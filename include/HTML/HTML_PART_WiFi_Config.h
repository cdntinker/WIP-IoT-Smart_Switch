
#ifndef config_form_WiFi_h
#define config_form_WiFi_h

const char config_form_WiFi[] PROGMEM = R"rawliteral(
<input id='host' name='host' maxlength='31' placeholder='hostname = %IDplaceholder%'><br/>
<input id='ssid' name='ssid' maxlength='31' placeholder='%IDssid%'><br/>
<input id='password' name='password' maxlength='63' type='password' placeholder='%whatpass%'><br/>
)rawliteral";

#endif  // config_form_WiFi_h