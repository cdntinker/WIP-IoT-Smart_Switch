/* Webpage HTML - this is for finished page (OTA success) */ 

#ifndef finished_h
#define finished_h

const char finished_html[] PROGMEM = R"rawliteral(
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
        <h3 align=center>Success!</h3>
        <h3 align=center></h3>
        <h3 align=center>Device Will Reboot</h3>
        <h3 align=center>and</h2>
        <h3 align=center>Load Home Page</h3>
        </div>
      </div>
%PART_Footer%
    </div>
  </body>
</html>
)rawliteral";

#endif
