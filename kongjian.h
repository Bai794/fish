/*** 
 * @Author: HideMe
 * @Date: 2021-12-21 22:45:54
 * @LastEditTime: 2021-12-21 22:54:09
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \fish\kongjian.h
 * @e-mail: 1269724114@qq.com
 */
#ifndef  KONGJIAN_H_H
#define  KONGJIAN_H_H
#include <Arduino.h>

struct  Component
{
    uint16_t x;
    uint16_t y;
    uint8_t attribute=0;//组件属性 0代表字符串 1代表数字
    uint8_t size;//代表组件字符的大小

    /* data */
};



#endif // ! KONGJIAN_H_H
