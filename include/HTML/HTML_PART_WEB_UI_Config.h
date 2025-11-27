
#ifndef config_form_WEB_UI_h
#define config_form_WEB_UI_h

const char config_form_WEB_UI[] PROGMEM = R"rawliteral(
<input id='htmltitle' name='htmltitle' maxlength='31' placeholder='html title = %title%'><br/>
<input id='htmltype' name='htmltype' maxlength='31' placeholder='html type = %type%'><br/>
<input id='dark' name='dark' maxlength='1' placeholder='%darkmode%' ><br/>
<input id='htmlcolor' name='htmlcolor' maxlength='7' placeholder='HTML Color' value='%color%' ><br/>
<input id='htmlhover' name='htmlhover' maxlength='7' placeholder='HTML Hover' value='%hover%' ><br/>
)rawliteral";

#endif  // config_form_WEB_UI_h