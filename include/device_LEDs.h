extern int SmartSwitch_LEDPin[4];
extern bool SmartSwitch_LED_STATE[4];
extern int LEDCount;

void LED_setup();

void LED_switch(int LEDNum, bool OnOff);

void LED_toggle(int LEDNum);
