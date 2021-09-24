/* Webpage HTML - this is for factory reset*/ 

#ifndef factory_html_h
#define factory_html_h

const char factory_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html5>
<html>
  <head>
    <title>%title% RESET</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
%The_CSS%
  </head>
  <body>
    <div id="container">
%PART_Header%
      <div id="body">    
        </br>
          <div class = "border">
            <h3 align=center>Factory Reset Performed</h3>
            <h3 align=center></h3>
            <h3 align=center>The device Will Now Be In AP Mode</h3>
            <h3 align=center></h3>
            <span class = "host">Navigate to %IDfactory% in wifi settings on mobile</span></br></br>
            <span class = "host">Once Connected to AP Navigate to 192.168.4.1 in Browser</span></br></br>
            <span class = "host">Visit the Config page</span></br></br>
            <span class = "host">Enter new Configuration</span></br></br>
            <span class = "host">Upon save the device will connect to specified WiFi SSID</span></br></br>
          </div>
          </br>
        </div>
%PART_Footer%
      </div>
      <script>
%The_SCRIPTS%
      </script>
  </body>
</html>
)rawliteral";
#endif
