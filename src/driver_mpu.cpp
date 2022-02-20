#include "driver_mpu.h"

MPU9250 mpu(0x69);

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

int16_t d;  //0 - normal 1 - top 2 - bottom

int16_t pre_ax=0, pre_ay=0, pre_az=0;
int16_t diff_ax, diff_ay, diff_az;
int avg_index = 0;
int sum_diff_a = 0;
std::queue<int> sum_diff_a_queue;
int avg_diff_a;

double yaw, pitch, row;

char* direction;
bool is_stable;

int count_check_direction = 0;
int count_check_stable = 0;

char* DIRECTION_0 = "0";
char* DIRECTION_1 = "1";
char* DIRECTION_2 = "2";

int STABLE_ACC_THRESHOLD = 2000;

bool STABLE_TRUE = true;
bool STABLE_FALSE = false;

int temp_direction;
bool temp_stable;

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

int mpu_get_direction()
{
    mpu_euler();
    if(row >= RTHRESHOLD_1 && row <= RTHRESHOLD_2){
        return 1;
    }else if(row <= -RTHRESHOLD_1 && row >= -RTHRESHOLD_2){
        return 2;
    }else{
        return 0;
    }
}

void mpu_update_direction()
{
  d = mpu_get_direction();
}

void mpu_update_6axis()
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
}

void mpu_update_6axis_diff()
{
    diff_ax = ax - pre_ax;
    if(diff_ax<0){
        diff_ax = -diff_ax;
    }
    pre_ax = ax;
    diff_ay = ay - pre_ay;
    if(diff_ay<0){
        diff_ay = -diff_ax;
    }
    pre_ay = ay;
    diff_az = az - pre_az;
    if(diff_az<0){
        diff_az = -diff_ax;
    }
    pre_az = az;
}

void mpu_update_diff_average()
{
    sum_diff_a = diff_ax + diff_ay + diff_az + sum_diff_a;
    sum_diff_a_queue.push(diff_ax+diff_ay+diff_az);
    if(sum_diff_a_queue.size()>=10){
        avg_diff_a = sum_diff_a/10;
        sum_diff_a -= sum_diff_a_queue.front();
        sum_diff_a_queue.pop();
    }
}

void mpu_direction_mqtt(char* subtopic_gyro, int interval)
{
    temp_direction = mpu_get_direction();
    if(temp_direction!=d){
        d = temp_direction;
        mqttpub_direction(subtopic_gyro, d);
        count_check_direction = 0;
    }else{
        if(count_check_direction>interval){
            mqttpub_direction(subtopic_gyro, d);
            count_check_direction = 0;
        }else{
            count_check_direction++;
        }
    }
}

void mpu_stable_mqtt(char* subtopic_gyro, int interval)
{
    mpu_update_6axis_diff();
    mpu_update_diff_average();
    temp_stable = avg_diff_a<STABLE_ACC_THRESHOLD;
    if(temp_stable!=is_stable){
        is_stable=temp_stable;
        mqttpub_stable(subtopic_gyro, is_stable);
        count_check_stable = 0;
    }else{
        if(count_check_stable>interval){
            mqttpub_stable(subtopic_gyro, is_stable);
            count_check_stable = 0;
        }else{
            count_check_stable++;
        }
    }
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

void mpu_show_diff()
{
    Serial.println("---------------------");
    Serial.println(diff_ax);
    Serial.println(diff_ay);
    Serial.println(diff_az);
    Serial.println(avg_diff_a);
}



