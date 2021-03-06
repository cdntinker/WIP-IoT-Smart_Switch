/* Webpage HTML - this is for reboot page */ 

#ifndef reboot_h
#define reboot_h

const char reboot_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html5>
<html>
  <head>
    <title>%title% Reboot</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <meta http-equiv="refresh" content="5; URL='/'" />
%The_CSS%
  </head>
  <body>
  <div id="container">
    <div id="header">
      <h2></h2>
    </div>
    <div id="body">
      <div class = "border">
      <h3 align=center>Device Will Reboot</h3>
      <h3 align=center>and</h3>
      <h3 align=center>Load Home Page</h3>
      </div>
    </div>
%PART_Footer%
    </div>
  </body>
</html>
)rawliteral";

#endif
