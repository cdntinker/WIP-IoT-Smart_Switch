
void SmartSwitch_init();

void SmartSwitch_Button(int ButtonNum);

void SmartSwitch_Relay(int RelayNum, bool OnOff);
void SmartSwitch_Toggle(int RelayNum);

void SmartSwitch_LED(int LEDNum, bool OnOff);
void SmartSwitch_LED_Toggle(int LEDNum);

void MQTT_HandleMessages(const char *Topic, const char *Message);
