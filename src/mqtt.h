#ifndef _MQTT_H_
#define _MQTT_H_

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <driver_mpu.h>

//extern WiFiClient espClient;
//extern PubSubClient client(WiFiClient);
extern const char* mqtt_server;
extern uint16_t mqtt_port;
extern String s;
extern char* mqtt_client_name;

extern char* MQTT_TOPIC_DIRECTION;
extern char* MQTT_TOPIC_STABLE;
extern char* MQTT_SUBTOPIC_LOCK;
extern char* MQTT_SUBTOPIC_HARNESS;

void mqtt_connect();
void mqtt_init(char* gyroName);
void mqttpub(char* gyroName);
void mqttpub_lock();
void mqttpub_harness();
void mqttpub_direction(char* gyroName, int direction);
void mqttpub_stable(char* gyroName, bool isStable);

extern String sday, smonth, syear;
extern String shour, sminute, ssecond, scentisecond;
extern char* getuptime();
extern bool radar_state();

//to be added
//mpu
extern int stibx;
extern char cver[3][2];
extern char nver[3][2];



#endif