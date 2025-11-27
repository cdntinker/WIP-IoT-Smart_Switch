/* Our Webpage needs SCRIPTS - this is them       */
/* main       - is script shared with most pages  */
/* management - is extra script used for the OTA  */

#ifndef SCRIPTS2_h
#define SCRIPTS2_h

const char CSS_SCRIPTS2[] PROGMEM = R"rawliteral(
  function mouseDown(x) {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/pressed?ID="+x, true);
    xhr.send();
  }

  function mouseUp(x) {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/released?ID="+x, true);
    xhr.send();
  }
      
  function darkFunction() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/darkmode?state=1", true);
    xhr.send();
    setTimeout(function () {window.location.reload();}, 100);
  }


  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage;
  }
  
  function onOpen(event) {
    console.log('Connection opened');
  }

  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }

  function onMessage(event) {
    <!-- console.log(event.data); -->
    var res = JSON.parse(event.data);
    document.getElementById('status0').style.borderColor = res.border0;
    document.getElementById('port0').style.color = res.port0;
    document.getElementById('volt0').style.color = res.voltstyle0;
    document.getElementById('volt0').innerHTML = res.volt0;
    document.getElementById('ma0').style.color = res.mastyle0;
    document.getElementById('ma0').innerHTML = res.ma0;
    document.getElementById('p0').innerHTML = res.p0;
    document.getElementById('d0').innerHTML = res.d0;

    document.getElementById('status1').style.borderColor = res.border1;
    document.getElementById('port1').style.color = res.port1;
    document.getElementById('volt1').style.color = res.voltstyle1;
    document.getElementById('volt1').innerHTML = res.volt1;
    document.getElementById('ma1').style.color = res.mastyle1;
    document.getElementById('ma1').innerHTML = res.ma1;
    document.getElementById('p1').innerHTML = res.p1;
    document.getElementById('d1').innerHTML = res.d1;

    document.getElementById('status2').style.borderColor = res.border2;
    document.getElementById('port2').style.color = res.port2;
    document.getElementById('volt2').style.color = res.voltstyle2;
    document.getElementById('volt2').innerHTML = res.volt2;
    document.getElementById('ma2').style.color = res.mastyle2;
    document.getElementById('ma2').innerHTML = res.ma2;
    document.getElementById('p2').innerHTML = res.p2;
    document.getElementById('d2').innerHTML = res.d2;

    document.getElementById('status3').style.borderColor = res.border3;
    document.getElementById('port3').style.color = res.port3;
    document.getElementById('volt3').style.color = res.voltstyle3;
    document.getElementById('volt3').innerHTML = res.volt3;
    document.getElementById('ma3').style.color = res.mastyle3;
    document.getElementById('ma3').innerHTML = res.ma3;
    document.getElementById('p3').innerHTML = res.p3;
    document.getElementById('d3').innerHTML = res.d3;
   }
  
  window.addEventListener('load', onLoad);
  
  function onLoad(event) {
    initWebSocket();
  }
<!-- End SCRIPTS 2 -->
)rawliteral";

#endif