#include "adc_bat.h"

ESP32AnalogRead adc_bat;

float bat_value;

void bat_init()
{
    adc_bat.attach(PIN_BAT_ADC);
}

void bat_show()
{
    bat_value = adc_bat.readVoltage() * 2;
    Serial.println("Bat:" + String(bat_value));
}