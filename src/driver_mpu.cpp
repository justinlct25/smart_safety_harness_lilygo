#include "driver_mpu.h"

MPU9250 mpu(0x69);

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

int16_t d;  //0 - normal 1 - top 2 - bottom

double yaw, pitch, row;

void mpu_init()
{
    Serial.print("MPU9250 Init : ");
    mpu.initialize();
}

void mpu_euler()
{
  pitch = -atan2(ax, sqrt(ay * ay + az * az));
  row = atan2(ay, az);
}

void mpu_direction()
{
  if(row >= RTHRESHOLD_1 && row <= RTHRESHOLD_2){
    d = 1;
  }else if(row <= -RTHRESHOLD_1 && row >= -RTHRESHOLD_2){
    d = 2;
  }else{
    d = 0;
  }
}

void mpu_update_vars()
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    mpu_euler();
    mpu_direction();
}

void mpu_show()
{
    Serial.println("---------------------");
    Serial.println(ax);
    Serial.println(ay);
    Serial.println(az);
    Serial.println(gx);
    Serial.println(gy);
    Serial.println(gz);
}


