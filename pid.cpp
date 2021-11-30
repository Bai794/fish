/***
 * @Author: HideMe
 * @Date: 2021-11-28 13:25:40
 * @LastEditTime: 2021-11-28 13:25:40
 * @LastEditors: your name
 * @Description:
 * @FilePath: \fish\control.cpp
 * @e-mail: 1269724114@qq.com
 */
#include "pid.h"
Mypid::Mypid(/* args */)
{
    this->p=0;
    this->i=0;
    this->d=0;
    this->pos_out=0;
    this->pid_mode=POSITION_PID;
}
void abs_limit(float *a, float ABS_MAX)
{
    if (*a > ABS_MAX)
        *a = ABS_MAX;
    if (*a < -ABS_MAX)
        *a = -ABS_MAX;
}

float Mypid::pid_calc(float get_value,float tagart)
{
    get[NOW]=get_value;
    Set[NOW]=tagart;
    err[NOW]=tagart-get_value;
    if(this->pid_mode==POSITION_PID)
    {

        pout=p*err[NOW];
        iout+=i*err[NOW];
        dout=d*(err[NOW]-err[LAST]);
        abs_limit(&iout,IntegralLimit);
        pos_out=pout+iout+dout;
        abs_limit(&pos_out,MaxOutout);
        last_pos_out=pos_out;

    }
    else if(pid_mode==DELTA_PID)
    {
        pout=p*(err[NOW]-err[LAST]);
        iout=i*err[NOW];
        dout=d*(err[NOW]-2*err[LAST]+err[LLAST]);
        abs_limit(&iout,IntegralLimit);
        delta_u=pout+iout+dout;
        delta_out=last_delta_out+delta_u;
        abs_limit(&delta_out,MaxOutout);
        pos_out=delta_out;
        last_delta_out=delta_out;
    }
    err[LLAST]=err[LAST];
    err[LAST]=err[NOW];

    get[LLAST]=get[LAST];
    get[LAST]=get[NOW];

    Set[LLAST]=Set[LAST];
    Set[LAST]=Set[NOW];
    return this->pos_out;
}

void Mypid::pid_init(float P,float I,float D,uint8_t PID_MODE,
                     uint32_t maxout, uint32_t intergral_limit)
{
    p=P;
    i=I;
    d=D;
    pid_mode=PID_MODE;
    MaxOutout=maxout;
    IntegralLimit=intergral_limit;

}
Mypid::~Mypid()
{

}
