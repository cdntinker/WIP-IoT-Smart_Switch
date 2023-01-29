/* Battery HTML */

#ifndef HTML_PART_Battery_h
#define HTML_PART_Battery_h

const char PART_battery_html[] PROGMEM = R"rawliteral(
<div class="name-battery" id="battery" style="background:%battColor%">
      <span class="name-text" id="batteryText">BAT</span>
      <span class="name-text" id="batteryVolts">%BATTERYv%</span>
</div>
)rawliteral";

#endif  // HTML_PART_Battery_h