To Be Done:
* Button Handling!!!
  * Getting there...
  * Need to indicate presses in the Web UI
  * Need to build in option for button presses to affect things like relay/LED control
    * Initial relay state seems to be unknown...  hhhmmm...
* Sensor handling
* Battery monitoring
  * Just needs adding to the Web UI now.
  * Need to figure out why bootup after battery death fails...
* Figure out a way to indicate active-low/active-high in the device descriptions
  * Maybe something involving negative numbers for the I/O numbers?
* Add a "Reboot" MQTT message
  * hhhmmm...
  * simple reboot works fine
  * factory reset seems to need power cycle before it does the AP reliably
* Make the Web UI reflect actual GPIO states
* LEDs
  * Why in hell can't I get the on-board LEDs on things to start out turned off???
  