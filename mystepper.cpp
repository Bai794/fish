/*** 
 * @Author: HideMe
 * @Date: 2021-11-17 11:09:33
 * @LastEditTime: 2021-11-17 11:09:33
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \fish\mystepper.cpp
 * @e-mail: 1269724114@qq.com
 */
 //100圈 50ml 22.4   10: 27  20:31.3 30
#include "mystepper.h"
mystepper::mystepper(int StepPin, int DirPin)
{
    stepPin = StepPin;
    dirPin = DirPin;
    pinMode(stepPin, OUTPUT);
    pinMode(DirPin, OUTPUT);
    speed =100;
    stepperStepPosition = 0;
    stepperStepTargetPosition = 0;
}
void mystepper::update()
{
    while (stepperStepTargetPosition < stepperStepPosition)
    {
        digitalWrite(dirPin, HIGH);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
        stepperStepPosition--;
    }
    while (stepperStepTargetPosition > stepperStepPosition)
    {
        digitalWrite(dirPin, LOW);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
        stepperStepPosition++;
    }
    stepperStepTargetPosition=0;
    stepperStepPosition=0;

}
void mystepper::setReductionRatio(float gearRatio, int stepsPerRev) //��һ�������Ǽ��ٱ�  �ڶ����Ƕ�������תһȦ
{
    radToStepFactor = gearRatio * stepsPerRev;
}
void mystepper::stepnum_turns(float quan_num)
{
    stepperStepTargetPosition = (int)(quan_num * (float)radToStepFactor + 0.5);
}
mystepper::~mystepper()
{
}
