/***
   @Author: HideMe
   @Date: 2021-11-28 21:04:32
   @LastEditTime: 2021-12-08 19:31:28
   @LastEditors: your name
   @Description:
   @FilePath: \fish\control.cpp
   @e-mail: 1269724114@qq.com
*/
#pragma once
#include "control.h"
#include <Arduino.h>
#include "pid.h"
#include "mytft.h"
#include "DS1302.h"
#include "pin.h"
#define wash_step 1
#define xi_HCL_step 2
#define xi_NAhco3_step 3

extern SYSTEMTIME DS1302Buffer;

float run_Scale = 0.5f;         //步进电机的圈数和容夜的比例
uint8_t times = 3, wash_v = 30; // 洗烧杯的次数 和每次洗的容夜
float user_tagart = 8.0f;       // 用户设定的水里的 nahco3的浓度
float user_Nahco3 = 100.0f;     //用户第一次nahco3加的量
float set_ph = 4.5;
extern void set_moterSpeed(int M, int speed);
extern float RedPh_value();
Mypid step;
float buffer[10] = {0};

mystepper stepper1(step1, dir1);
mystepper stepper2(step2, dir2);
mystepper stepper3(step3, dir3);

void step_init()
{
  stepper1.setReductionRatio(1, 200 * 16); //
  stepper2.setReductionRatio(1, 200 * 16);
  stepper3.setReductionRatio(1, 200 * 16);
}
void Pid_init()
{
  step.pid_init(0.01, 0.001, 0.02, POSITION_PID, 1, 1);
}
/***
   @description: 确锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟揭癸拷锟斤拷锟斤拷锟斤拷锟斤拷怨锟较碉拷锟斤拷锟斤拷诒锟斤拷锟斤拷锟斤拷锟絩un_Scale
   @function:
   @param {int} m  确锟斤拷锟斤拷锟斤拷一锟斤拷锟斤拷锟?
   @param {float} ml  锟斤拷要锟斤拷取锟斤拷锟斤拷夜
   @return {*}
*/

void run_step(int m, float ml)
{
  float tagart_quan = ml / run_Scale;
  if (m == 1)
  {
    stepper1.stepnum_turns(tagart_quan);
    stepper1.update();
  }
  else if (m == 2)
  {
    stepper2.stepnum_turns(tagart_quan);
    stepper2.update();
  }
  else if (m == 3)
  {
    stepper3.stepnum_turns(tagart_quan);
    stepper3.update();
  }
  else
    return;
}
/***
   @description: 洗锟秸憋拷锟侥猴拷锟斤拷
   @function:   通锟斤拷锟街憋拷锟睫革拷times wash_num锟斤拷锟斤拷锟斤拷确锟斤拷锟秸憋拷洗锟斤拷锟轿猴拷每锟斤拷洗锟秸憋拷水锟斤拷锟斤拷锟斤拷
   @param {*}
   @return {*}
*/
void wash_Cup()
{

  for (int i = 0; i < times; i++)
  {
    run_step(wash_step, wash_v);
    set_moterSpeed(1, 500); //锟斤拷锟斤拷
    delay(1000);
    set_moterSpeed(1, 0);
    delay(4000);
  }
}
void add_nahco3(float user_Nahco3)
{
  run_step(xi_NAhco3_step, user_Nahco3);
}
/***
   @description: 改函数是返回hcl 的体积
   @function:
   @param {*}
   @return {*}
*/
float control_ph(float tagart_ph)
{
  float v = 0.0f, get, sum = 0, times = 0;
  while (1)
  {
    get = RedPh_value();
    float num = step.pid_calc(get, tagart_ph);
    sum += num;
    run_step(xi_HCL_step, num);
    if (fabs(step.err[NOW]) < 0.05)
    {
      times++;
      if (times >= 5)
        break;
    }
  }
  return sum; //返回hcl的体积
}

void chou_water(int speed, float v)
{
  set_moterSpeed(1, speed);
  delay((int)(v / speed));
  set_moterSpeed(1, 0);
}
/***
   @description:
   @function:
   @param {*}
   @return {*}
*/
void one_action()
{
  wash_Cup();
  float one_hcl = control_ph(set_ph);
  chou_water(600, 300); //
  add_nahco3(user_Nahco3);
  float two_hcl = control_ph(set_ph);
  float multiple = (user_tagart - two_hcl) / (two_hcl - one_hcl);
  add_nahco3(user_Nahco3 * multiple);
}
void tft_show()
{
  char time_str[30];
  sprintf(time_str, "%d-%d-%d-%d:%d week:%d", DS1302Buffer.Year + 2002, DS1302Buffer.Month,
          DS1302Buffer.Day, DS1302Buffer.Hour, DS1302Buffer.Minute, DS1302Buffer.Week);
  LCD_ShowString(44, 36, 240, 16, 16, (const char *)time_str);
}
void tft_satrt()
{
  LCD_ShowString(10, 54, 240, 16, 16, "PH:");
  LCD_ShowString(40, 54, 240, 16, 16, String(set_ph).c_str());
  LCD_ShowString(100, 54, 240, 16, 16, "tagart:");
  LCD_ShowString(160, 54, 240, 16, 16, String(user_tagart).c_str());
  LCD_ShowString(10, 72, 240, 16, 16, "F_NA:");
  LCD_ShowString(50, 72, 240, 16, 16, String(user_Nahco3).c_str());
  LCD_ShowString(100, 72, 240, 16, 16, "scale:");
  LCD_ShowString(160, 72, 240, 16, 16, String(run_Scale).c_str());
}
