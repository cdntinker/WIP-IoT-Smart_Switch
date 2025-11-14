To Be Done:
* Firmware update needs help...
* Button Handling!!!
  * Getting there...
  * AAARRRGGG... Is it bouncing or is it sending the MQTT twice???
    * Bloody Sonoff Basic seems to need debouncing!
    * err...  now it's just fine...
* Sensor handling
* Battery monitoring
  * Just needs adding to the Web UI now.
* Figure out a way to indicate active-low/active-high in the device descriptions
  * Maybe something involving negative numbers for the I/O numbers?
* Add a "Reboot" MQTT message
  * hhhmmm...
  * simple reboot works fine.
  * factory reset seems to need power cycle before it does the AP reliably.
