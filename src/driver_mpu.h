#ifndef _DRIVER_MPU_H_
#define _DRIVER_MPU_H_

#include "pin_define.h"

#include "MPU9250.h"

#define RTHRESHOLD_1 0.8
#define RTHRESHOLD_2 2.2

extern int16_t ax, ay, az;
extern int16_t gx, gy, gz;
extern int16_t mx, my, mz;

void mpu_init();
void mpu_euler();
void mpu_direction();
void mpu_update_vars();
void mpu_show();

#endif
