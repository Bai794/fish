/***
 * @Author: HideMe
 * @Date: 2021-11-28 13:25:50
 * @LastEditTime: 2021-11-28 13:43:25
 * @LastEditors: your name
 * @Description:
 * @FilePath: \fish\control.h
 * @e-mail: 1269724114@qq.com
 */
#ifndef PID_H_
#define PID_H_
typedef unsigned char   uint8_t;
typedef unsigned int    uint32_t;
enum
{
    LLAST	= 0,
    LAST 	= 1,
    NOW 	= 2,

    POSITION_PID,
    DELTA_PID,
};
void abs_limit(float *a, float ABS_MAX);
class Mypid
{
private:
    /* data */
public:
    Mypid(/* args */);
    ~Mypid();
    float pid_calc(float get_value,float tagart);
    void pid_init(float P,float I,float D,uint8_t PID_MODE,
                  uint32_t maxout, uint32_t intergral_limit);
    float p,i,d;
    float Set[3],get[3],err[3];//include NOW LAST LLAST
    float pout,iout,dout;
    float pos_out,last_pos_out,delta_u,delta_out,last_delta_out;
    uint8_t pid_mode;
    uint32_t MaxOutout;
    uint32_t IntegralLimit;
};




#endif // !CONTROL_H_
