/* Header HTML */ 

#ifndef PART_HomePage_Body_h
#define PART_HomePage_Body_h

const char PART_HomePage_Body[] PROGMEM = R"rawliteral(
<div class = "border">
<font size=1>Relays</font>

%OTOButtons.Relays%
</div>

<div class = "border">
<font size=1>LEDs</font>

%OTOButtons.LEDs%
</div>

<div class = "border">
<font size=1>Buttons</font>

%OTOInputs.Buttons%
</div>

<div class = "border">
<font size=1>Inputs_direct</font>

%OTOInputs.Inputs_direct%
</div>


<div class = "border">
<font size=1>Inputs_sensors</font>

%OTOInputs.Inputs_sensors%
</div>

)rawliteral";

#endif  // PART_HomePage_Body_h