extern unsigned int GPIO_Relay_PINS[4];
extern bool GPIO_Relay_STATE[10];
extern unsigned int GPIO_Relay_COUNT;

void Relay_setup();

void Relay_switch(int RelayNum, bool OnOff);

void Relay_toggle(int RelayNum);
