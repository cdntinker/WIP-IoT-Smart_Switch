# Current state of the project

At this moment, Relays and LEDs on devices are being handled.

# TODO items

Add Group Topic to the config page.

Simplify handling of Active-High vs. Active-Low LEDs.

Handling on-device buttons is highest priority.

Sensors of various sorts would be rather nice.

# Usage
## To build in PlatformIO...

You can either just download the repo & open the folder in VSCode or actually Clone the repository directly.

**Build it.**

## To build in Tarduino...

Make sure you have the ESP8266 set up in your copy of Tarduino:

[How to](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/)

Install the needed libraries:

* ArduinoJson
* PubSubClient
* ESP Async WebServer
    * [How to](https://reacoda.gitbook.io/molemi-iot/introducing-the-nodemcu/display-the-dht11-sensor-reading-on-a-web-server-using-nodemcu./installing-dht-library-on-the-esp8266/installing-the-asynchronous-web-server-library)
* Adafruit NeoPixel
* https://github.com/cdntinker/TinkerLibs-DEBUG
    * (Instructions in the README.md of that repo...)
    
Create a folder named `IdIoT` inside your Arduino folder, copy the content of `src` & `include` to that folder & rename `IdIoT.cpp` to `IdIoT.ino`

Tell Tarduino to open `IdIoT.ino`...

Eeewww...  Ick!  :vomiting_face:
