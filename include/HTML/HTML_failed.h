/* Webpage HTML - this is for failed page (OTA failure or other) */ 

#ifndef failed_h
#define failed_h

const char failed_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html5>
<html>
  <head>
    <title>%title% FAIL</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
%The_CSS%
  </head>
  <body>
    <div id="container">
%PART_Header%
      <div id="body">    
        <div class = "border">
        <h3 align=center>Oh No!!!</h3>
        <h3 align=center></h3>
        <h3 align=center>It Borked!!!</h3>
        <h3 align=center></h3>
        <h3 align=center>What'd ya try to do?</h3>
        </div>
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
