extern unsigned int GPIO_LED_PINS[4];
extern bool GPIO_LED_STATE[10];
extern unsigned int GPIO_LED_COUNT;

void LED_setup();

void LED_switch(int LEDNum, bool OnOff);

void LED_toggle(int LEDNum);
