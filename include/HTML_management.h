/* Webpage HTML - this is for management page (OTA update)*/ 

#ifndef management_h
#define management_h

const char management_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html5>
<html>
  <head>
    <title>%title% Management</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">

    %The_CSS%

  </head>
  <body>
    <div id="container">

%PART_Header%

     <div id="body">

       <div class = "menu-buttons">
         <div class = "border">
           <div class = "buttons ButtonClickable">
             <button5 onclick="location.href='/reboot'">%processorplaceholder% Reboot</button5>
           </div>
         </div>
       </div>

       <div class = "border">
         <div class="col-12 mt-3 p-centered">
           <label class="label label2 mr-2">Upload Firmware Here</label>
           <div class="form-group pt-2 mt-3">
             <form method="POST" action="#" enctype="multipart/form-data" id="upload_form">
               <input type="file" name="update" id="file" accept=".bin" class="form-input file-input">
               <input type="submit" value="FLASH">
               <div class="upload-bar">
                 <div class="w3-background">
                   <div class="w3-progress" id="prg1" style="width: 0rem">
                     <span class="percent" id="prg">-</span>
                 </div>
               </div>
             </form>
           </div>
         </div>
       </div>
     </div>

%PART_DeviceInfo%

       <div class = "menu-buttons">
         <div class = "border">
           <div class = "buttons ButtonClickable">
             <button6 onclick="location.href='/factory'">Factory Reset</button6>
           </div>
         </div>
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