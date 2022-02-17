#include "mqtt.h"

WiFiClient espClient;
PubSubClient mqttclient(espClient);
const char* mqtt_server = "18.162.55.224";
uint16_t mqtt_port = 9000;
String s=";";
int id = 0;


void mqtt_init(){
    mqttclient.setServer(mqtt_server, mqtt_port);
    mqttclient.connect("smart_safety_harness");
}



void mqttpub_lock(){
  if (!mqttclient.connected()) {
    Serial.println("mqtt broker not connected. Reconnecting ...");
    mqttclient.connect("smart_access_card");
    delay(500);
  }
  else{
    String data = String(ax)+", "+String(ay)+", "+String(az) +", "+String(gy)+", "+String(gx)+", "+String(gz);
    mqttclient.publish("/lock", data.c_str());
    Serial.println("lock published");
  }
}

void mqttpub_harness(){
  if (!mqttclient.connected()) {
    Serial.println("mqtt broker not connected. Reconnecting ...");
    mqttclient.connect("smart_access_card");
    delay(500);
  }
  else{
    String data = String(ax)+", "+String(ay)+", "+String(az) +", "+String(gy)+", "+String(gx)+", "+String(gz);
    mqttclient.publish("/harness", data.c_str());
    Serial.println("harness published");
  }
}