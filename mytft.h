/*** 
 * @Author: HideMe
 * @Date: 2021-11-24 15:41:03
 * @LastEditTime: 2021-11-24 15:41:03
 * @LastEditors: your name
 * @Description: 
 * @FilePath: \fish\mytft.h
 * @e-mail: 1269724114@qq.com
 */
#ifndef MYTFT_H_
#define MYTFT_H_
#include <Adafruit_GFX.h>    // Core graphics library by Adafruit
#include <Arduino_ST7789.h> // Hardware-specific library for ST7789 (with or without CS pin)
#include <SPI.h>


extern Arduino_ST7789 tft;


void tftPrintTest();
void mediabuttons();
void testroundrects();//
void testtriangles();
void testdrawcircles(uint8_t radius, uint16_t color);
void testfillcircles(uint8_t radius, uint16_t color);
void testfillrects(uint16_t color1, uint16_t color2);
void testdrawrects(uint16_t color);
void testfastlines(uint16_t color1, uint16_t color2);
void testdrawtext(char *text, uint16_t color) ;
void testlines(uint16_t color);
#endif // !MYTFT_H
