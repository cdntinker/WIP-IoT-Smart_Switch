extern int SmartSwitch_RelayPin[4];
extern bool SmartSwitch_Relay_STATE[4];
extern int RelayCount;

void Relay_switch(int RelayNum, bool OnOff);

void Relay_toggle(int RelayNum);
