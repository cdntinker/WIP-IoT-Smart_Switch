#ifndef mqtt_setup_h
#define mqtt_setup_h

#include <Arduino.h>

void MQTT_settopics();
void MQTT_callback(char *topic, byte *payload, unsigned int length);
// void MQTT_HandleMessages(const char *MQTT_command, const char *MQTT_msg_in);
void MQTT_reconnect();

void MQTT_init();
void MQTT_loop();

void MQTT_send(const char* Topic, char Buffer[40]);

/* Special for UT61E */
void MQTT_JSON_send(char g_mqtt_json_topic[50], size_t msg_length, bool TF, char g_json_message_buffer[512]);

////////////////////////////////////////////////////////////////////////////
//  These translate the TinkerLibs MQTT function calls to IdIoT calls //
////////////////////////////////////////////////////////////////////////////
void MQTT_SendSTAT(const char *Topic, const char *Message);
void MQTT_SendNOTI(const char *Topic, const char *Message);
void MQTT_SendTELE(const char *Topic, const char *Message);

#endif
