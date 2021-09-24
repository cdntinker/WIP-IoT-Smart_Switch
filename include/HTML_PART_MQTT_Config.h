
#ifndef config_form_MQTT_h
#define config_form_MQTT_h

const char config_form_MQTT[] PROGMEM = R"rawliteral(
<input id='mqtt' name='mqtt' maxlength='31' placeholder='%broker%'><br/>
<input id='port' name='port' maxlength='4' placeholder='%port%'><br/>
<br/>
<input id='mqttuser' name='mqttuser' maxlength='31' placeholder='%userID%'><br/>
<input id='mqttpass' name='mqttpass' maxlength='31' type='password' placeholder='%notpass%'><br/>
)rawliteral";

#endif  // config_form_MQTT_h