#include "mqtt.h"

WiFiClient espClient;
PubSubClient mqttclient(espClient);
const char* mqtt_server = "18.162.55.224";
uint16_t mqtt_port = 9000;
String s=";";
int id = 0;
char* mqtt_client_name;

char* MQTT_TOPIC_DIRECTION = "/direction";
char* MQTT_TOPIC_STABLE = "/stable";
char* MQTT_SUBTOPIC_LOCK = "/lock";
char* MQTT_SUBTOPIC_HARNESS = "/harness";

void mqtt_connect(){
    mqttclient.connect(mqtt_client_name);
    Serial.println(mqtt_client_name);
    Serial.println("mqtt connected");
}

void mqtt_init(char* gyroName){
    mqttclient.setServer(mqtt_server, mqtt_port);
    mqtt_client_name = gyroName;
    mqtt_connect();
}

void mqttpub(char* gyroName){
  if (!mqttclient.connected()) {
    Serial.println("mqtt broker not connected. Reconnecting ...");
    mqttclient.connect(gyroName);
    delay(500);
  }
  else{
    String data = String(gyroName)+", "+String(ax)+", "+String(ay)+", "+String(az) +", "+String(d);
    mqttclient.publish("/lock_harness", data.c_str());
    Serial.println("lock published");
  }
}


void mqttpub_lock(){
  if (!mqttclient.connected()) {
    Serial.println("mqtt broker not connected. Reconnecting ...");
    mqtt_connect();
    delay(500);
  }
  else{
    String data = String(ax)+", "+String(ay)+", "+String(az) +", "+String(gx)+", "+String(gy)+", "+String(gz)+", "+String(d)+", "+String(avg_diff_a);
    mqttclient.publish("/lock", data.c_str());
    Serial.println("lock published");
  }
}

void mqttpub_harness(){
  if (!mqttclient.connected()) {
    Serial.println("mqtt broker not connected. Reconnecting ...");
    mqtt_connect();
    delay(500);
  }
  else{
    String data = String(ax)+", "+String(ay)+", "+String(az) +", "+String(gx)+", "+String(gy)+", "+String(gz)+", "+String(d)+", "+String(avg_diff_a);
    mqttclient.publish("/harness", data.c_str());
    Serial.println("harness published");
  }
}

void mqttpub_direction(char* gyroName, int direction){
  if (!mqttclient.connected()) {
    Serial.println("mqtt broker not connected. Reconnecting ...");
    mqtt_connect();
    delay(500);
  }
  else{
    std::string s;
    s += MQTT_TOPIC_DIRECTION;
    s += gyroName;
    mqttclient.publish(s.c_str(), String(direction).c_str());
    Serial.println("direction published");
  }
}

void mqttpub_stable(char* gyroName, bool isStable){
  if (!mqttclient.connected()) {
    Serial.println("mqtt broker not connected. Reconnecting ...");
    mqtt_connect();
    delay(500);
  }
  else{
    std::string s;
    s += MQTT_TOPIC_STABLE;
    s += gyroName;
    mqttclient.publish(s.c_str(), isStable?"1":"0");
    Serial.println("stable published");
  }
}