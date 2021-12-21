/***
 * @Author: HideMe
 * @Date: 2021-11-17 11:09:33
 * @LastEditTime: 2021-11-17 11:09:33
 * @LastEditors: your name
 * @Description:
 * @FilePath: \fish\mystepper.cpp
 * @e-mail: 1269724114@qq.com
 */
// 100闁革讣鎷� 50ml 22.4   10: 27  20:31.3 30
#include "mystepper.h"
#include "pin.h"

mystepper::mystepper(int StepPin, int DirPin)
{
    stepPin = StepPin;
    dirPin = DirPin;
    pinMode(stepPin, OUTPUT);
    pinMode(DirPin, OUTPUT);
    speed = 100;
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
    stepperStepTargetPosition = 0;
    stepperStepPosition = 0;
}
void mystepper::setReductionRatio(float gearRatio, int stepsPerRev) //闁跨喐鏋婚幏铚傜闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撶憴鎺斻€嬮幏鐑芥晸閸旑偅鍞婚幏锟�  闁跨喕濡拋瑙勫闁跨喐鏋婚幏鐑芥晸鐟欐帟顔愰幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻弬銈嗗鏉烆兛绔撮崷锟�
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
