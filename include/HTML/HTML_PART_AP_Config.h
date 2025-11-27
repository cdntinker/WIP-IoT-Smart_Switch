
#ifndef config_form_AP_h
#define config_form_AP_h

const char config_form_AP[] PROGMEM = R"rawliteral(
<input id='apssid' name='apssid' maxlength='31' placeholder='%apss%'><br/>
<input id='appass' name='appass' maxlength='63' type='password' placeholder='%passwhat%' minlength='8'><br/>
<input id='hidden' name='hidden' maxlength='1' placeholder='%aphid%'><br/>
)rawliteral";

#endif  // config_form_AP_h