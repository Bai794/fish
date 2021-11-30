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
float run_Scale = 0.2f;         //���������ҹ���������Թ�ϵ
uint8_t times = 3, wash_v = 30; // times ��ʾ����ϴ���ӵĴ��� ,wah_num ��ʾ����ˮ����
float user_tagart = 8.0f;       // �û��趨�������ˮnahco3Ũ��
float user_Nahco3 = 10.0f;      //��һ���û��ӵ�nahco3����
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
 * @description: ȷ�������������ҹ���������Թ�ϵ�����ڱ�������run_Scale
 * @function:    
 * @param {int} m  ȷ������һ�����
 * @param {float} ml  ��Ҫ��ȡ����ҹ
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
 * @description: ϴ�ձ��ĺ���
 * @function:   ͨ���ֱ��޸�times wash_num������ȷ���ձ�ϴ���κ�ÿ��ϴ�ձ�ˮ������
 * @param {*}
 * @return {*}
 */
void wash_Cup()
{

    for (int i = 0; i < times; i++)
    {
        run_step(wash_step, wash_v);
        set_moterSpeed(1, 500); //����
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
 * @description: �ĺ������ڶ��ձ��������ﵽph4.5���ƺ��� ������nahco3��Ũ��
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
    return sum; //�������õ����
}

void chou_water(int speed, float v)
{
    set_moterSpeed(1, speed);
    delay((int)(v / speed));
    set_moterSpeed(1, 0);
}
/*** 
 * @description: ִ��һ�β����ĺ���
 * @function: 
 * @param {*}
 * @return {*}
 */
void one_action()
{
    wash_Cup();
    float one_hcl = control_ph(set_ph);
    chou_water(600, 300); //600���ٶ��ų� 300ml�����ձ�����ҹ
    add_nahco3(user_Nahco3);
    float two_hcl = control_ph(set_ph);
    float multiple = (user_tagart - two_hcl) / (two_hcl - one_hcl);
    add_nahco3(user_Nahco3 * multiple);
    add_nahco3(user_Nahco3 * multiple);
    
}