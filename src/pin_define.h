#ifndef _PIN_DEFINE_H_
#define _PIN_DEFINE_H_

#include <Arduino.h>

#define PIN_LED 4

//TOUCH PAD
#define PIN_TOUCH_POW 25
#define PIN_TOUCH_PAD 33

#define PIN_BAT_ADC 35

#define PIN_VBUS_ADC 36

//MPU9250
#define PIN_MPU_INT 39
#define PIN_MPU_SDA 21
#define PIN_MPU_SCL 22

//ST7735
// #define PIN_TFT_MISO NULL
// #define PIN_TFT_MOSI 19
// #define PIN_TFT_SCLK 18
// #define PIN_TFT_CS 5
// #define PIN_TFT_DC 23
// #define PIN_TFT_RST 26
// #define PIN_TFT_BL 27

//RTC Chip PCF8563
#define PIN_RTC_INT 34

//全局
#define BAT_MISTAKE 0

//
extern float bat_value;

#endif
