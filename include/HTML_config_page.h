/* config page HTML - this is the config page - lets the user set their information for the device */ 
/* Can be accessed via AP or on wifi mode */

#ifndef config_page_h
#define config_page_h

const char config_form[] PROGMEM = R"rawliteral(
<!DOCTYPE html5>
<html>
  <head>
    <title>%title% Config</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <meta http-equiv="expires" content="0">
%The_CSS%
  </head>
  <body>
  
    <div id="container">

%PART_Header%

    <div id="body"> 

      <!--<input id="sum" name="sum" maxlength="3" type='password' placeholder="sum" value="" {c}><br/>-->

      <div class = "border">

        <form method='get' action='wifisave'>

%config_form_WiFi%
        <br/>
%config_form_AP%
        <br/>
%config_form_MQTT%
        <br/>
%config_form_WEB_UI%
        <br/>
%config_form_LEDs%
      
        <br/><button class = "buttons ButtonClickable" type='submit'>save</button></form>
      
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

#endif // config_page_h