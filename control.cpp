/*** 
 * @Author: HideMe
 * @Date: 2021-11-28 21:04:32
 * @LastEditTime: 2021-11-30 18:36:06
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \fish\control.cpp
 * @e-mail: 1269724114@qq.com
 */
#include "control.h"
#include <Arduino.h>
#include "pid.h"
#include "mystepper.h"

#define wash_step 1
#define xi_HCL_step 2
#define xi_NAhco3_step 3

extern mystepper mystepper1, mystepper2, mystepper3;
float run_Scale = 0.2f;         //进电机与容夜毫升的线性关系
uint8_t times = 3, wash_v = 30; // times 表示初次洗杯子的次数 ,wah_num 表示出的水多少
float user_tagart = 8.0f;       // 用户设定的鱼池里水nahco3浓度
float user_Nahco3 = 10.0f;      //第一次用户加的nahco3的量
float set_ph = 4.5;
extern void set_moterSpeed(int M, int speed);
extern float RedPh_value();
Mypid step;
float buffer[10] = {0};

void Pid_init()
{
    step.pid_init(0.01, 0.001, 0.02, POSITION_PID, 1, 1);
}
/*** 
 * @description: 确定步进电机与容夜毫升的线性关系，调节比例变量run_Scale
 * @function:    
 * @param {int} m  确定是哪一个电机
 * @param {float} ml  需要吸取的容夜
 * @return {*}
 */

void run_step(int m, float ml)
{
    float tagart_quan = ml / run_Scale;
    if (m == 1)
    {
        mystepper1.stepnum_turns(tagart_quan);
        mystepper1.update();
    }
    else if (m == 2)
    {
        mystepper2.stepnum_turns(tagart_quan);
        mystepper2.update();
    }
    else if (m == 3)
    {
        mystepper3.stepnum_turns(tagart_quan);
        mystepper3.update();
    }
    else
        return;
}
/*** 
 * @description: 洗烧杯的函数
 * @function:   通过分别修改times wash_num变量来确定烧杯洗几次和每次洗烧杯水的容量
 * @param {*}
 * @return {*}
 */
void wash_Cup()
{

    for (int i = 0; i < times; i++)
    {
        run_step(wash_step, wash_v);
        set_moterSpeed(1, 500); //搅拌
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
 * @description: 改函数用于对烧杯里的盐酸达到ph4.5控制函数 返回所nahco3的浓度
 * @function: 
 * @param {*}
 * @return {*}
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
    return sum; //返回所用的体积
}

void chou_water(int speed, float v)
{
    set_moterSpeed(1, speed);
    delay((int)(v / speed));
    set_moterSpeed(1, 0);
}
/*** 
 * @description: 执行一次测量的函数
 * @function: 
 * @param {*}
 * @return {*}
 */
void one_action()
{
    wash_Cup();
    float one_hcl = control_ph(set_ph);
    chou_water(600, 300); //600的速度排除 300ml里面烧杯的容夜
    add_nahco3(user_Nahco3);
    float two_hcl = control_ph(set_ph);
    float multiple = (user_tagart - two_hcl) / (two_hcl - one_hcl);
    add_nahco3(user_Nahco3 * multiple);
    add_nahco3(user_Nahco3 * multiple);
    
}