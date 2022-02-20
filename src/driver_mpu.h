#ifndef _DRIVER_MPU_H_
#define _DRIVER_MPU_H_

#include "pin_define.h"

#include "MPU9250.h"

#define RTHRESHOLD_1 0.8
#define RTHRESHOLD_2 2.2

#include <queue>

#include "mqtt.h"

extern int16_t ax, ay, az;
extern int16_t gx, gy, gz;
extern int16_t mx, my, mz;
extern int16_t d;
extern int16_t diff_ax, diff_ay, diff_az;
extern int avg_diff_a;
extern char* direction;
extern bool is_stable;

extern char* DIRECTION_0;
extern char* DIRECTION_1;
extern char* DIRECTION_2;
extern bool STABLE_TRUE, STABLE_FALSE;

void mpu_init();
void mpu_euler();
int mpu_get_direction();
void mpu_update_direction();
void mpu_update_6axis();
void mpu_update_6axis_diff();
void mpu_update_diff_average();
void mpu_direction_mqtt(char* subtopic_gyro, int interval);
void mpu_stable_mqtt(char* subtopic_gyro, int interval);

void mpu_show();
void mpu_show_diff();

#endif
