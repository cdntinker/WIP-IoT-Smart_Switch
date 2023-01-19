/* Battery HTML */

#ifndef HTML_PART_Battery_h
#define HTML_PART_Battery_h

const char PART_battery_html[] PROGMEM = R"rawliteral(
<div class = "name-battery" id="battery" style="%online%">
      <span class = "name-text">BAT: %BATTERYv%</span>
</div>
)rawliteral";

#endif  // HTML_PART_Battery_h