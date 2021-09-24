#include <Arduino.h>

#if defined(ESP32)
String return_reset_reason(RESET_REASON reason);
#endif
String DeviceID();
String info_memsketch();
String ip3string(IPAddress ip);
String processor(const String &var);
