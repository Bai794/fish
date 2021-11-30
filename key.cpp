/*** 
 * @Author: HideMe
 * @Date: 2021-11-26 20:03:35
 * @LastEditTime: 2021-11-26 20:03:35
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \fish\key.cpp
 * @e-mail: 1269724114@qq.com
 */
#include "key.h"
#include "pin.h"
#include <Arduino.h>
void Pin_init()
{
    pinMode(sw1, INPUT);
    pinMode(sw2, INPUT);
    pinMode(sw3, INPUT); // SW1 SW2 SW3 通过外接上拉电阻实现按键

    pinMode(sw4, INPUT_PULLUP);
    pinMode(sw5, INPUT_PULLUP);
    pinMode(sw6, INPUT_PULLUP);
}