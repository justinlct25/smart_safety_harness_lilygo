#include "pin_define.h"

#include "adc_bat.h"
//#include "driver_tft.h"
#include "driver_mpu.h"
// #include "bluetooth.h"
#include "wifi_c.h"
#include "mqtt.h"

u_long loop_temp_time;

void init() {

  Serial.begin(115200);
  Wire.begin();

  // bluetooth_init();
  //LED
  //pinMode(PIN_LED, OUTPUT);
  //digitalWrite(PIN_LED, LOW);

  //BAT
  bat_init();
  //TFT
  //tft_init();
  //MPU
  mpu_init();

  wifi_init();
  delay(500);
  // mqtt_init("Lock");
  mqtt_init("Harness");
  delay(500);
}

void setup() {
  init();
}

void loop() {

  if(millis() - loop_temp_time >= 500)
  {
    loop_temp_time = millis();
    Serial.println("----------" + String(millis()) + "----------");
    
    if(!wifi_stat()){
      Serial.println("wifi not connected");
      wifi_init();
      delay(500);
      mqtt_connect();
      delay(500);
    }

    bat_show();
    mpu_update_6axis();
    Serial.println("direction, stable");
    // mpu_direction_mqtt("/lock", 20);
    // mpu_stable_mqtt("/lock", 20);
    mpu_direction_mqtt("/harness", 10);
    mpu_stable_mqtt("/harness", 10);

    // mpu_show();
    // mpu_update_diff_average();
    // mpu_show_diff();

    // mqttpub("Lock");
    // mqttpub_lock();
    // mqttpub_harness();
  }
}