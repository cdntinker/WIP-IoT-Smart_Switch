/* Header HTML */ 
 
#ifndef PART_HomePage_Body_h
#define PART_HomePage_Body_h

const char PART_HomePage_Body[] PROGMEM = R"rawliteral(
)rawliteral";

#ifdef SmartSwitch_Relays
const char PART_HomePage_Body_Relays[] PROGMEM = R"rawliteral(
<div class = "border">
%OTOButtons.Relays%
</div>
)rawliteral";
#else
const char PART_HomePage_Body_Relays[] PROGMEM = R"rawliteral(
)rawliteral";
#endif

#ifdef SmartSwitch_LEDs
const char PART_HomePage_Body_LEDs[] PROGMEM = R"rawliteral(
<div class = "border">
%OTOButtons.LEDs%
</div>
)rawliteral";
#else
const char PART_HomePage_Body_LEDs[] PROGMEM = R"rawliteral(
)rawliteral";
#endif

#ifdef SmartSwitch_Buttons
const char PART_HomePage_Body_Buttons[] PROGMEM = R"rawliteral(
<div class = "border">
%OTOInputs.Buttons%
</div>
)rawliteral";
#else
const char PART_HomePage_Body_Buttons[] PROGMEM = R"rawliteral(
)rawliteral";
#endif

#ifdef SmartSwitch_Inputs_Direct
const char PART_HomePage_Body_Inputs_direct[] PROGMEM = R"rawliteral(
<div class = "border">
%OTOInputs.Inputs_direct%
</div>
)rawliteral";
#else
const char PART_HomePage_Body_Inputs_direct[] PROGMEM = R"rawliteral(
)rawliteral";
#endif

#ifdef SmartSwitch_Inputs_Sensors
const char PART_HomePage_Body_Inputs_sensors[] PROGMEM = R"rawliteral(
<div class = "border">
%OTOInputs.Inputs_sensors%
</div>
)rawliteral";
#else
const char PART_HomePage_Body_Inputs_sensors[] PROGMEM = R"rawliteral(
)rawliteral";
#endif

#endif  // PART_HomePage_Body_h