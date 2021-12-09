/*** 
 * @Author: HideMe
 * @Date: 2021-11-17 11:09:50
 * @LastEditTime: 2021-11-17 18:37:07
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \fish\mystepper.h
 * @e-mail: 1269724114@qq.com
 */
#ifndef MYSTEPPER_H_
#define MYSTEPPER_H_
#include <Arduino.h>
class mystepper
{
private:
    /* data */
    int stepPin;
    int dirPin;
    int stepperStepTargetPosition;
    int stepperStepPosition;
    int speed;
    int radToStepFactor;

public:
    mystepper(int StepPin, int DirPin);
    ~mystepper();
    void update();
    void setReductionRatio(float gearRatio, int stepsPerRev);
    void stepnum_turns(float quan_num); //����ת����Ȧ
};
#endif
