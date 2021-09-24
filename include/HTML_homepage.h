/* Webpage HTML - this is the homepage*/ 

#ifndef homepage_h
#define homepage_h

const char home_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html5>
<html>
  <head>
    <title>%title% Home</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <meta http-equiv="expires" content="0">
%The_CSS%
  </head>
  <body>
    <div id="container">
%PART_Header%
      <div id="body"> 
%PART_HomePage_Body%
        <br>
%PART_DeviceInfo%
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