
#ifndef config_form_SmartHUB_h
#define config_form_SmartHUB_h

const char config_form_SmartHUB[] PROGMEM = R"rawliteral(
<br/>

<input id='systemcurrent' name='systemcurrent' maxlength='4' placeholder='%currentsys%'><br/>

<br/>

<input id='currentone' name='currentone' maxlength='4' placeholder='%current1%'><br/>
<input id='currenttwo' name='currenttwo' maxlength='4' placeholder='%current2%'><br/>
<input id='currentthree' name='currentthree' maxlength='4' placeholder='%current3%'><br/>
<input id='currentfour' name='currentfour' maxlength='4' placeholder='%current4%'><br/>

<br/>

<input id='overmode' name='overmode' maxlength='4' placeholder='%modeover2%'><br/>
<input id='overwifi' name='overwifi' maxlength='4' placeholder='%wifiover%'><br/>
)rawliteral";

#endif  // config_form_SmartHUB_h