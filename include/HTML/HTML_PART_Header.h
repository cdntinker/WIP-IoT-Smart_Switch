/* Header HTML */ 

#ifndef HTML_PART_Header_h
#define HTML_PART_Header_h

const char PART_Header_html[] PROGMEM = R"rawliteral(
<div id="header">
    <h2>%title% - <em>%PageName%</em></h2>
    %ALLDAButtons%
    %PART_status%
    %PART_battery%
</div>
)rawliteral";

#endif  // HTML_PART_Header_h