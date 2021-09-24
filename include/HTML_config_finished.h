/* Webpage HTML - this is for finished page (OTA success) */ 

#ifndef config_finished_h
#define config_finished_h


const char finished_config[] PROGMEM = R"rawliteral(
<!DOCTYPE html5>
<html>
  <head>
    <title>Woo Hoo!!!</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <meta http-equiv="refresh" content="5; URL='/'" />
%The_CSS%
  </head>
  <body>
    <div id="container">
      <div id="header">
        <h2>Woo Hoo!!!</h2>
      </div>
      <div id="body">
        <div class = "border">
          <h3 align=center>Config Saved</h3>
          <h3 align=center></h3>
          <h3 align=center>Device Will:</h3>
          <span class = "host">A) Reboot if needed</span></br>
          <span class = "host">B) Reload Home Page</span></br>
          <span class = "host">C) Start WiFi and Disable AP</span></br></br>
          <span class = "host">Look For The Device On Your Network As Needed</span></br>
        </div>
        </br>
      </div>
%PART_Footer%
    </div>
  </body>
</html>
)rawliteral";

#endif
