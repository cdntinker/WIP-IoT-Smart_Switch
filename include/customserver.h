void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *WSclient, AwsEventType type,
             void *arg, uint8_t *data, size_t len);
void initWebSocket();
void OTA_Restart();
boolean customInit();

void WEB_cleanupClients();
void WEB_textAll(String buf);
