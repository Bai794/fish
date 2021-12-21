/*** 
 * @Author: HideMe
 * @Date: 2021-12-09 14:05:28
 * @LastEditTime: 2021-12-21 22:05:58
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \fish\control.h
 * @e-mail: 1269724114@qq.com
 */
/***
 * @Author: HideMe
 * @Date: 2021-11-28 21:04:43
 * @LastEditTime: 2021-12-08 19:31:32
 * @LastEditors: your name
 * @Description:
 * @FilePath: \fish\control.h
 * @e-mail: 1269724114@qq.com
 */
#ifndef CONTROL_H_
#define CONTROL_H_
#include "mystepper.h"

void tft_show();
void Pid_init();
void wash_Cup();
void run_step(int m, float ml);
void add_nahco3(float user_Nahco3);
float control_ph(float tagart_ph);
void chou_water(int speed, float v);
void one_action();
void tft_satrt();
void step_init();
extern mystepper stepper1,stepper3,stepper2;
#endif // !CONTROL_H_
