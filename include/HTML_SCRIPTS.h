/* Our Webpage needs SCRIPTS - this is them       */
/* main       - is script shared with most pages  */
/* management - is extra script used for the OTA  */


#ifndef SCRIPTS_h
#define SCRIPTS_h

const char CSS_SCRIPTS[] PROGMEM = R"rawliteral(


function darkFunction() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/darkmode?state=1", true);
  xhr.send();
  setTimeout(function () {window.location.reload();}, 100);
}

/*    Control Button Handling       */

function RelayON() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/RelayControl?state=1", true);
  xhr.send();
  setTimeout(function () {window.location.reload();}, 100);
}

function RelayOFF() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/RelayControl?state=0", true);
  xhr.send();
  setTimeout(function () {window.location.reload();}, 100);
}

function RelayTOGGLE() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/RelayControl?state=9", true);
  xhr.send();
  setTimeout(function () {window.location.reload();}, 100);
} 

/*    ///////////////////////////////////////   */

   function checkConnectionStatus()
   {
    let xhttp = new XMLHttpRequest();
    xhttp.timeout = 2000;
    xhttp.onreadystatechange = function()
    {
        if (this.readyState == 4)
        {
            if (this.status === 200)
            {
                document.getElementById("state").style.background = this.responseText;
            }
            else
            {
                document.getElementById("state").style.background = "red";
            }
             setTimeout(checkConnectionStatus, 5000);
            /* Repeat our status check only once there's a result */
        }
    }
    xhttp.open("GET", "/state", true);
    xhttp.send();
}

/*    Initial status check    */
setTimeout(checkConnectionStatus, 5000);

var domReady = function(callback) {
       document.readyState === "interactive" || document.readyState === "complete" ? callback() : document.addEventListener("DOMContentLoaded", callback);
      };

     domReady(function() {
       var myform = document.getElementById('upload_form');
       var filez  = document.getElementById('file');

       myform.onsubmit = function(event) {
         event.preventDefault();

         var formData = new FormData();
         var file     = filez.files[0];

         if (!file) { return false; }

         formData.append("files", file, file.name);

         var xhr = new XMLHttpRequest();
         xhr.upload.addEventListener("progress", function(evt) {
           if (evt.lengthComputable) {
             var per  = Math.round((evt.loaded / evt.total) * 100);
             var per1 = Math.round(per/4);
             var prg  = document.getElementById('prg');
             var prg1 = document.getElementById('prg1');

             prg1.style.width  = per1 + "rem"
             prg.innerHTML     = per + "%"
            }
          }, false);
          xhr.open('POST', location.href, true);

         /* Set up a handler for when the request finishes. */
         xhr.onload = function () {
           if (xhr.status === 200) {
             //alert('Success');
             window.location.href = "/complete";
            } else {
             //alert('An error occurred!');
             window.location.href = "/failedOTA";
            }
          };

         xhr.send(formData);
        }
      });

)rawliteral";

#endif
