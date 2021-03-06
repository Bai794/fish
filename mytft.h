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
#include <Arduino.h>
#include "stdlib.h"

#define u16 unsigned short
#define u8 unsigned char
#define u32 unsigned int
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// LCDï¿½ï¿½Òªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
typedef struct
{
  u16 width;  // LCD ï¿½ï¿½ï¿?
  u16 height; // LCD ï¿½ß¶ï¿½
  u16 id;     // LCD ID
  u8 dir;     //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ£ï¿½0ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½1ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
  u8 wramcmd; //ï¿½ï¿½Ê¼Ð´gramÖ¸ï¿½ï¿½
  u8 setxcmd; //ï¿½ï¿½ï¿½ï¿½xï¿½ï¿½ï¿½ï¿½Ö¸ï¿½ï¿½
  u8 setycmd; //ï¿½ï¿½ï¿½ï¿½yï¿½ï¿½ï¿½ï¿½Ö¸ï¿½ï¿½
} _lcd_dev;

// LCDï¿½ï¿½ï¿½ï¿½
extern _lcd_dev lcddev; //ï¿½ï¿½ï¿½ï¿½LCDï¿½ï¿½Òªï¿½ï¿½ï¿½ï¿½
// LCDï¿½Ä»ï¿½ï¿½ï¿½ï¿½ï¿½É«ï¿½Í±ï¿½ï¿½ï¿½É«
extern u16 POINT_COLOR; //Ä¬ï¿½Ïºï¿½É«
extern u16 BACK_COLOR;  //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½É«.Ä¬ï¿½ï¿½Îªï¿½ï¿½É«

//////////////////////////////////////////////////////////////////////////////////

//-----------------LCDï¿½Ë¿Ú¶ï¿½ï¿½ï¿½----------------
#define LCD_RESET 21 // LCDï¿½ï¿½Î»

#define LCD_CS 2   //Æ¬Ñ¡ï¿½Ë¿ï¿½
#define LCD_RS 0   //ï¿½ï¿½ï¿½ï¿½/ï¿½ï¿½ï¿½ï¿½
#define LCD_SCL 22 //Ð´ï¿½ï¿½ï¿½ï¿½
#define LCD_SDA 23 //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
//#define LCD_SDO PCin(0)   //PC0    SDO

//É¨ï¿½è·½ï¿½ï¿½ï¿½ï¿½
#define L2R_U2D 0 //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½,ï¿½ï¿½ï¿½Ïµï¿½ï¿½ï¿½
#define L2R_D2U 1 //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½,ï¿½ï¿½ï¿½Âµï¿½ï¿½ï¿½
#define R2L_U2D 2 //ï¿½ï¿½ï¿½Òµï¿½ï¿½ï¿½,ï¿½ï¿½ï¿½Ïµï¿½ï¿½ï¿½
#define R2L_D2U 3 //ï¿½ï¿½ï¿½Òµï¿½ï¿½ï¿½,ï¿½ï¿½ï¿½Âµï¿½ï¿½ï¿½

#define U2D_L2R 4 //ï¿½ï¿½ï¿½Ïµï¿½ï¿½ï¿½,ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
#define U2D_R2L 5 //ï¿½ï¿½ï¿½Ïµï¿½ï¿½ï¿½,ï¿½ï¿½ï¿½Òµï¿½ï¿½ï¿½
#define D2U_L2R 6 //ï¿½ï¿½ï¿½Âµï¿½ï¿½ï¿½,ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
#define D2U_R2L 7 //ï¿½ï¿½ï¿½Âµï¿½ï¿½ï¿½,ï¿½ï¿½ï¿½Òµï¿½ï¿½ï¿½

extern u8 DFT_SCAN_DIR;

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½É«
#define WHITE 0xffff
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40 //ï¿½ï¿½É«
#define BRRED 0XFC07 //ï¿½Øºï¿½É«
#define GRAY 0X8430  //ï¿½ï¿½É«
// GUIï¿½ï¿½É«

#define DARKBLUE 0X01CF  //ï¿½ï¿½ï¿½ï¿½É«
#define LIGHTBLUE 0X7D7C //Ç³ï¿½ï¿½É«
#define GRAYBLUE 0X5458  //ï¿½ï¿½ï¿½ï¿½É«
//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½É«ÎªPANELï¿½ï¿½ï¿½ï¿½É«

#define LIGHTGREEN 0X841F //Ç³ï¿½ï¿½É«
//#define LIGHTGRAY        0XEF5B //Ç³ï¿½ï¿½É«(PANNEL)
#define LGRAY 0XC618 //Ç³ï¿½ï¿½É«(PANNEL),ï¿½ï¿½ï¿½å±³ï¿½ï¿½É«

#define LGRAYBLUE 0XA651 //Ç³ï¿½ï¿½ï¿½ï¿½É«(ï¿½Ð¼ï¿½ï¿½ï¿½ï¿½É?)
#define LBBLUE 0X2B12    //Ç³ï¿½ï¿½ï¿½ï¿½É«(Ñ¡ï¿½ï¿½ï¿½ï¿½Ä¿ï¿½Ä·ï¿½É«)

void LCD_Init(void);                                                                //ï¿½ï¿½Ê¼ï¿½ï¿½
void LCD_DisplayOn(void);                                                           //ï¿½ï¿½ï¿½ï¿½Ê¾
void LCD_DisplayOff(void);                                                          //ï¿½ï¿½ï¿½ï¿½Ê¾
void LCD_Clear(u16 Color);                                                          //ï¿½ï¿½ï¿½ï¿½
void LCD_SetCursor(u16 Xpos, u16 Ypos);                                             //ï¿½ï¿½ï¿½Ã¹ï¿½ï¿?
void LCD_DrawPoint(u16 x, u16 y);                                                   //ï¿½ï¿½ï¿½ï¿½
void LCD_Fast_DrawPoint(u16 x, u16 y, u16 color);                                   //ï¿½ï¿½ï¿½Ù»ï¿½ï¿½ï¿½
u16 LCD_ReadPoint(u16 x, u16 y);                                                    //ï¿½ï¿½ï¿½ï¿½
void Draw_Circle(u16 x0, u16 y0, u8 r);                                             //ï¿½ï¿½Ô²
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);                                  //ï¿½ï¿½ï¿½ï¿½
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);                             //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color);                           //ï¿½ï¿½äµ¥É?
void LCD_Color_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 *color);                    //ï¿½ï¿½ï¿½Ö¸ï¿½ï¿½ï¿½ï¿½É?
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 size, u8 mode);                          //ï¿½ï¿½Ê¾Ò»ï¿½ï¿½ï¿½Ö·ï¿½
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size);                           //ï¿½ï¿½Ê¾Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
void LCD_ShowxNum(u16 x, u16 y, u32 num, u8 len, u8 size, u8 mode);                 //ï¿½ï¿½Ê¾ ï¿½ï¿½ï¿½ï¿½
void LCD_ShowString(u16 x, u16 y, u16 width, u16 height, u8 size, const char *ptr); //ï¿½ï¿½Ê¾Ò»ï¿½ï¿½ï¿½Ö·ï¿½ï¿½ï¿½,12/16ï¿½ï¿½ï¿½ï¿½
void LCD_Set_Window(u16 sx, u16 sy, u16 width, u16 height);
void IO_init(void);
void LCD_Showfloat(u16 x, u16 y, u16 width, u16 height, u8 size, float num);
void LCD_WR_REG(u8);
void LCD_WR_DATA(u16);
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
void LCD_Scan_Dir(u8 dir);    //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½É¨ï¿½è·½ï¿½ï¿½
void LCD_Display_Dir(u8 dir); //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä»ï¿½ï¿½Ê¾ï¿½ï¿½ï¿½ï¿½

// 9320/9325 LCDï¿½Ä´ï¿½ï¿½ï¿½
#define R0 0x00
#define R1 0x01
#define R2 0x02
#define R3 0x03
#define R4 0x04
#define R5 0x05
#define R6 0x06
#define R7 0x07
#define R8 0x08
#define R9 0x09
#define R10 0x0A
#define R12 0x0C
#define R13 0x0D
#define R14 0x0E
#define R15 0x0F
#define R16 0x10
#define R17 0x11
#define R18 0x12
#define R19 0x13
#define R20 0x14
#define R21 0x15
#define R22 0x16
#define R23 0x17
#define R24 0x18
#define R25 0x19
#define R26 0x1A
#define R27 0x1B
#define R28 0x1C
#define R29 0x1D
#define R30 0x1E
#define R31 0x1F
#define R32 0x20
#define R33 0x21
#define R34 0x22
#define R36 0x24
#define R37 0x25
#define R40 0x28
#define R41 0x29
#define R43 0x2B
#define R45 0x2D
#define R48 0x30
#define R49 0x31
#define R50 0x32
#define R51 0x33
#define R52 0x34
#define R53 0x35
#define R54 0x36
#define R55 0x37
#define R56 0x38
#define R57 0x39
#define R59 0x3B
#define R60 0x3C
#define R61 0x3D
#define R62 0x3E
#define R63 0x3F
#define R64 0x40
#define R65 0x41
#define R66 0x42
#define R67 0x43
#define R68 0x44
#define R69 0x45
#define R70 0x46
#define R71 0x47
#define R72 0x48
#define R73 0x49
#define R74 0x4A
#define R75 0x4B
#define R76 0x4C
#define R77 0x4D
#define R78 0x4E
#define R79 0x4F
#define R80 0x50
#define R81 0x51
#define R82 0x52
#define R83 0x53
#define R96 0x60
#define R97 0x61
#define R106 0x6A
#define R118 0x76
#define R128 0x80
#define R129 0x81
#define R130 0x82
#define R131 0x83
#define R132 0x84
#define R133 0x85
#define R134 0x86
#define R135 0x87
#define R136 0x88
#define R137 0x89
#define R139 0x8B
#define R140 0x8C
#define R141 0x8D
#define R143 0x8F
#define R144 0x90
#define R145 0x91
#define R146 0x92
#define R147 0x93
#define R148 0x94
#define R149 0x95
#define R150 0x96
#define R151 0x97
#define R152 0x98
#define R153 0x99
#define R154 0x9A
#define R157 0x9D
#define R192 0xC0
#define R193 0xC1
#define R229 0xE5

const unsigned char asc2_1206[95][12] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*" ",0*/
    {0x00, 0x00, 0x00, 0x00, 0x3F, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"!",1*/
    {0x00, 0x00, 0x30, 0x00, 0x40, 0x00, 0x30, 0x00, 0x40, 0x00, 0x00, 0x00}, /*""",2*/
    {0x09, 0x00, 0x0B, 0xC0, 0x3D, 0x00, 0x0B, 0xC0, 0x3D, 0x00, 0x09, 0x00}, /*"#",3*/
    {0x18, 0xC0, 0x24, 0x40, 0x7F, 0xE0, 0x22, 0x40, 0x31, 0x80, 0x00, 0x00}, /*"$",4*/
    {0x18, 0x00, 0x24, 0xC0, 0x1B, 0x00, 0x0D, 0x80, 0x32, 0x40, 0x01, 0x80}, /*"%",5*/
    {0x03, 0x80, 0x1C, 0x40, 0x27, 0x40, 0x1C, 0x80, 0x07, 0x40, 0x00, 0x40}, /*"&",6*/
    {0x10, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"'",7*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x20, 0x40, 0x40, 0x20}, /*"(",8*/
    {0x00, 0x00, 0x40, 0x20, 0x20, 0x40, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00}, /*")",9*/
    {0x09, 0x00, 0x06, 0x00, 0x1F, 0x80, 0x06, 0x00, 0x09, 0x00, 0x00, 0x00}, /*"*",10*/
    {0x04, 0x00, 0x04, 0x00, 0x3F, 0x80, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00}, /*"+",11*/
    {0x00, 0x10, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*",",12*/
    {0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00}, /*"-",13*/
    {0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*".",14*/
    {0x00, 0x20, 0x01, 0xC0, 0x06, 0x00, 0x38, 0x00, 0x40, 0x00, 0x00, 0x00}, /*"/",15*/
    {0x1F, 0x80, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x1F, 0x80, 0x00, 0x00}, /*"0",16*/
    {0x00, 0x00, 0x10, 0x40, 0x3F, 0xC0, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00}, /*"1",17*/
    {0x18, 0xC0, 0x21, 0x40, 0x22, 0x40, 0x24, 0x40, 0x18, 0x40, 0x00, 0x00}, /*"2",18*/
    {0x10, 0x80, 0x20, 0x40, 0x24, 0x40, 0x24, 0x40, 0x1B, 0x80, 0x00, 0x00}, /*"3",19*/
    {0x02, 0x00, 0x0D, 0x00, 0x11, 0x00, 0x3F, 0xC0, 0x01, 0x40, 0x00, 0x00}, /*"4",20*/
    {0x3C, 0x80, 0x24, 0x40, 0x24, 0x40, 0x24, 0x40, 0x23, 0x80, 0x00, 0x00}, /*"5",21*/
    {0x1F, 0x80, 0x24, 0x40, 0x24, 0x40, 0x34, 0x40, 0x03, 0x80, 0x00, 0x00}, /*"6",22*/
    {0x30, 0x00, 0x20, 0x00, 0x27, 0xC0, 0x38, 0x00, 0x20, 0x00, 0x00, 0x00}, /*"7",23*/
    {0x1B, 0x80, 0x24, 0x40, 0x24, 0x40, 0x24, 0x40, 0x1B, 0x80, 0x00, 0x00}, /*"8",24*/
    {0x1C, 0x00, 0x22, 0xC0, 0x22, 0x40, 0x22, 0x40, 0x1F, 0x80, 0x00, 0x00}, /*"9",25*/
    {0x00, 0x00, 0x00, 0x00, 0x08, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*":",26*/
    {0x00, 0x00, 0x00, 0x00, 0x04, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*";",27*/
    {0x00, 0x00, 0x04, 0x00, 0x0A, 0x00, 0x11, 0x00, 0x20, 0x80, 0x40, 0x40}, /*"<",28*/
    {0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x00, 0x00}, /*"=",29*/
    {0x00, 0x00, 0x40, 0x40, 0x20, 0x80, 0x11, 0x00, 0x0A, 0x00, 0x04, 0x00}, /*">",30*/
    {0x18, 0x00, 0x20, 0x00, 0x23, 0x40, 0x24, 0x00, 0x18, 0x00, 0x00, 0x00}, /*"?",31*/
    {0x1F, 0x80, 0x20, 0x40, 0x27, 0x40, 0x29, 0x40, 0x1F, 0x40, 0x00, 0x00}, /*"@",32*/
    {0x00, 0x40, 0x07, 0xC0, 0x39, 0x00, 0x0F, 0x00, 0x01, 0xC0, 0x00, 0x40}, /*"A",33*/
    {0x20, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x24, 0x40, 0x1B, 0x80, 0x00, 0x00}, /*"B",34*/
    {0x1F, 0x80, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x30, 0x80, 0x00, 0x00}, /*"C",35*/
    {0x20, 0x40, 0x3F, 0xC0, 0x20, 0x40, 0x20, 0x40, 0x1F, 0x80, 0x00, 0x00}, /*"D",36*/
    {0x20, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x2E, 0x40, 0x30, 0xC0, 0x00, 0x00}, /*"E",37*/
    {0x20, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x2E, 0x00, 0x30, 0x00, 0x00, 0x00}, /*"F",38*/
    {0x0F, 0x00, 0x10, 0x80, 0x20, 0x40, 0x22, 0x40, 0x33, 0x80, 0x02, 0x00}, /*"G",39*/
    {0x20, 0x40, 0x3F, 0xC0, 0x04, 0x00, 0x04, 0x00, 0x3F, 0xC0, 0x20, 0x40}, /*"H",40*/
    {0x20, 0x40, 0x20, 0x40, 0x3F, 0xC0, 0x20, 0x40, 0x20, 0x40, 0x00, 0x00}, /*"I",41*/
    {0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x3F, 0xC0, 0x20, 0x00, 0x20, 0x00}, /*"J",42*/
    {0x20, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x0B, 0x00, 0x30, 0xC0, 0x20, 0x40}, /*"K",43*/
    {0x20, 0x40, 0x3F, 0xC0, 0x20, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0xC0}, /*"L",44*/
    {0x3F, 0xC0, 0x3C, 0x00, 0x03, 0xC0, 0x3C, 0x00, 0x3F, 0xC0, 0x00, 0x00}, /*"M",45*/
    {0x20, 0x40, 0x3F, 0xC0, 0x0C, 0x40, 0x23, 0x00, 0x3F, 0xC0, 0x20, 0x00}, /*"N",46*/
    {0x1F, 0x80, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x1F, 0x80, 0x00, 0x00}, /*"O",47*/
    {0x20, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x24, 0x00, 0x18, 0x00, 0x00, 0x00}, /*"P",48*/
    {0x1F, 0x80, 0x21, 0x40, 0x21, 0x40, 0x20, 0xE0, 0x1F, 0xA0, 0x00, 0x00}, /*"Q",49*/
    {0x20, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x26, 0x00, 0x19, 0xC0, 0x00, 0x40}, /*"R",50*/
    {0x18, 0xC0, 0x24, 0x40, 0x24, 0x40, 0x22, 0x40, 0x31, 0x80, 0x00, 0x00}, /*"S",51*/
    {0x30, 0x00, 0x20, 0x40, 0x3F, 0xC0, 0x20, 0x40, 0x30, 0x00, 0x00, 0x00}, /*"T",52*/
    {0x20, 0x00, 0x3F, 0x80, 0x00, 0x40, 0x00, 0x40, 0x3F, 0x80, 0x20, 0x00}, /*"U",53*/
    {0x20, 0x00, 0x3E, 0x00, 0x01, 0xC0, 0x07, 0x00, 0x38, 0x00, 0x20, 0x00}, /*"V",54*/
    {0x38, 0x00, 0x07, 0xC0, 0x3C, 0x00, 0x07, 0xC0, 0x38, 0x00, 0x00, 0x00}, /*"W",55*/
    {0x20, 0x40, 0x39, 0xC0, 0x06, 0x00, 0x39, 0xC0, 0x20, 0x40, 0x00, 0x00}, /*"X",56*/
    {0x20, 0x00, 0x38, 0x40, 0x07, 0xC0, 0x38, 0x40, 0x20, 0x00, 0x00, 0x00}, /*"Y",57*/
    {0x30, 0x40, 0x21, 0xC0, 0x26, 0x40, 0x38, 0x40, 0x20, 0xC0, 0x00, 0x00}, /*"Z",58*/
    {0x00, 0x00, 0x00, 0x00, 0x7F, 0xE0, 0x40, 0x20, 0x40, 0x20, 0x00, 0x00}, /*"[",59*/
    {0x00, 0x00, 0x70, 0x00, 0x0C, 0x00, 0x03, 0x80, 0x00, 0x40, 0x00, 0x00}, /*"\",60*/
    {0x00, 0x00, 0x40, 0x20, 0x40, 0x20, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00}, /*"]",61*/
    {0x00, 0x00, 0x20, 0x00, 0x40, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"^",62*/
    {0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10}, /*"_",63*/
    {0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"`",64*/
    {0x00, 0x00, 0x02, 0x80, 0x05, 0x40, 0x05, 0x40, 0x03, 0xC0, 0x00, 0x40}, /*"a",65*/
    {0x20, 0x00, 0x3F, 0xC0, 0x04, 0x40, 0x04, 0x40, 0x03, 0x80, 0x00, 0x00}, /*"b",66*/
    {0x00, 0x00, 0x03, 0x80, 0x04, 0x40, 0x04, 0x40, 0x06, 0x40, 0x00, 0x00}, /*"c",67*/
    {0x00, 0x00, 0x03, 0x80, 0x04, 0x40, 0x24, 0x40, 0x3F, 0xC0, 0x00, 0x40}, /*"d",68*/
    {0x00, 0x00, 0x03, 0x80, 0x05, 0x40, 0x05, 0x40, 0x03, 0x40, 0x00, 0x00}, /*"e",69*/
    {0x00, 0x00, 0x04, 0x40, 0x1F, 0xC0, 0x24, 0x40, 0x24, 0x40, 0x20, 0x00}, /*"f",70*/
    {0x00, 0x00, 0x02, 0xE0, 0x05, 0x50, 0x05, 0x50, 0x06, 0x50, 0x04, 0x20}, /*"g",71*/
    {0x20, 0x40, 0x3F, 0xC0, 0x04, 0x40, 0x04, 0x00, 0x03, 0xC0, 0x00, 0x40}, /*"h",72*/
    {0x00, 0x00, 0x04, 0x40, 0x27, 0xC0, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00}, /*"i",73*/
    {0x00, 0x10, 0x00, 0x10, 0x04, 0x10, 0x27, 0xE0, 0x00, 0x00, 0x00, 0x00}, /*"j",74*/
    {0x20, 0x40, 0x3F, 0xC0, 0x01, 0x40, 0x07, 0x00, 0x04, 0xC0, 0x04, 0x40}, /*"k",75*/
    {0x20, 0x40, 0x20, 0x40, 0x3F, 0xC0, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00}, /*"l",76*/
    {0x07, 0xC0, 0x04, 0x00, 0x07, 0xC0, 0x04, 0x00, 0x03, 0xC0, 0x00, 0x00}, /*"m",77*/
    {0x04, 0x40, 0x07, 0xC0, 0x04, 0x40, 0x04, 0x00, 0x03, 0xC0, 0x00, 0x40}, /*"n",78*/
    {0x00, 0x00, 0x03, 0x80, 0x04, 0x40, 0x04, 0x40, 0x03, 0x80, 0x00, 0x00}, /*"o",79*/
    {0x04, 0x10, 0x07, 0xF0, 0x04, 0x50, 0x04, 0x40, 0x03, 0x80, 0x00, 0x00}, /*"p",80*/
    {0x00, 0x00, 0x03, 0x80, 0x04, 0x40, 0x04, 0x50, 0x07, 0xF0, 0x00, 0x10}, /*"q",81*/
    {0x04, 0x40, 0x07, 0xC0, 0x02, 0x40, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00}, /*"r",82*/
    {0x00, 0x00, 0x06, 0x40, 0x05, 0x40, 0x05, 0x40, 0x04, 0xC0, 0x00, 0x00}, /*"s",83*/
    {0x00, 0x00, 0x04, 0x00, 0x1F, 0x80, 0x04, 0x40, 0x00, 0x40, 0x00, 0x00}, /*"t",84*/
    {0x04, 0x00, 0x07, 0x80, 0x00, 0x40, 0x04, 0x40, 0x07, 0xC0, 0x00, 0x40}, /*"u",85*/
    {0x04, 0x00, 0x07, 0x00, 0x04, 0xC0, 0x01, 0x80, 0x06, 0x00, 0x04, 0x00}, /*"v",86*/
    {0x06, 0x00, 0x01, 0xC0, 0x07, 0x00, 0x01, 0xC0, 0x06, 0x00, 0x00, 0x00}, /*"w",87*/
    {0x04, 0x40, 0x06, 0xC0, 0x01, 0x00, 0x06, 0xC0, 0x04, 0x40, 0x00, 0x00}, /*"x",88*/
    {0x04, 0x10, 0x07, 0x10, 0x04, 0xE0, 0x01, 0x80, 0x06, 0x00, 0x04, 0x00}, /*"y",89*/
    {0x00, 0x00, 0x04, 0x40, 0x05, 0xC0, 0x06, 0x40, 0x04, 0x40, 0x00, 0x00}, /*"z",90*/
    {0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x7B, 0xE0, 0x40, 0x20, 0x00, 0x00}, /*"{",91*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00}, /*"|",92*/
    {0x00, 0x00, 0x40, 0x20, 0x7B, 0xE0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"}",93*/
    {0x40, 0x00, 0x80, 0x00, 0x40, 0x00, 0x20, 0x00, 0x20, 0x00, 0x40, 0x00}, /*"~",94*/
};
const unsigned char asc2_1608[95][16] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*" ",0*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xCC, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"!",1*/
    {0x00, 0x00, 0x08, 0x00, 0x30, 0x00, 0x60, 0x00, 0x08, 0x00, 0x30, 0x00, 0x60, 0x00, 0x00, 0x00}, /*""",2*/
    {0x02, 0x20, 0x03, 0xFC, 0x1E, 0x20, 0x02, 0x20, 0x03, 0xFC, 0x1E, 0x20, 0x02, 0x20, 0x00, 0x00}, /*"#",3*/
    {0x00, 0x00, 0x0E, 0x18, 0x11, 0x04, 0x3F, 0xFF, 0x10, 0x84, 0x0C, 0x78, 0x00, 0x00, 0x00, 0x00}, /*"$",4*/
    {0x0F, 0x00, 0x10, 0x84, 0x0F, 0x38, 0x00, 0xC0, 0x07, 0x78, 0x18, 0x84, 0x00, 0x78, 0x00, 0x00}, /*"%",5*/
    {0x00, 0x78, 0x0F, 0x84, 0x10, 0xC4, 0x11, 0x24, 0x0E, 0x98, 0x00, 0xE4, 0x00, 0x84, 0x00, 0x08}, /*"&",6*/
    {0x08, 0x00, 0x68, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"'",7*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xE0, 0x18, 0x18, 0x20, 0x04, 0x40, 0x02, 0x00, 0x00}, /*"(",8*/
    {0x00, 0x00, 0x40, 0x02, 0x20, 0x04, 0x18, 0x18, 0x07, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*")",9*/
    {0x02, 0x40, 0x02, 0x40, 0x01, 0x80, 0x0F, 0xF0, 0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x00, 0x00}, /*"*",10*/
    {0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x0F, 0xF8, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00}, /*"+",11*/
    {0x00, 0x01, 0x00, 0x0D, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*",",12*/
    {0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80}, /*"-",13*/
    {0x00, 0x00, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*".",14*/
    {0x00, 0x00, 0x00, 0x06, 0x00, 0x18, 0x00, 0x60, 0x01, 0x80, 0x06, 0x00, 0x18, 0x00, 0x20, 0x00}, /*"/",15*/
    {0x00, 0x00, 0x07, 0xF0, 0x08, 0x08, 0x10, 0x04, 0x10, 0x04, 0x08, 0x08, 0x07, 0xF0, 0x00, 0x00}, /*"0",16*/
    {0x00, 0x00, 0x08, 0x04, 0x08, 0x04, 0x1F, 0xFC, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00}, /*"1",17*/
    {0x00, 0x00, 0x0E, 0x0C, 0x10, 0x14, 0x10, 0x24, 0x10, 0x44, 0x11, 0x84, 0x0E, 0x0C, 0x00, 0x00}, /*"2",18*/
    {0x00, 0x00, 0x0C, 0x18, 0x10, 0x04, 0x11, 0x04, 0x11, 0x04, 0x12, 0x88, 0x0C, 0x70, 0x00, 0x00}, /*"3",19*/
    {0x00, 0x00, 0x00, 0xE0, 0x03, 0x20, 0x04, 0x24, 0x08, 0x24, 0x1F, 0xFC, 0x00, 0x24, 0x00, 0x00}, /*"4",20*/
    {0x00, 0x00, 0x1F, 0x98, 0x10, 0x84, 0x11, 0x04, 0x11, 0x04, 0x10, 0x88, 0x10, 0x70, 0x00, 0x00}, /*"5",21*/
    {0x00, 0x00, 0x07, 0xF0, 0x08, 0x88, 0x11, 0x04, 0x11, 0x04, 0x18, 0x88, 0x00, 0x70, 0x00, 0x00}, /*"6",22*/
    {0x00, 0x00, 0x1C, 0x00, 0x10, 0x00, 0x10, 0xFC, 0x13, 0x00, 0x1C, 0x00, 0x10, 0x00, 0x00, 0x00}, /*"7",23*/
    {0x00, 0x00, 0x0E, 0x38, 0x11, 0x44, 0x10, 0x84, 0x10, 0x84, 0x11, 0x44, 0x0E, 0x38, 0x00, 0x00}, /*"8",24*/
    {0x00, 0x00, 0x07, 0x00, 0x08, 0x8C, 0x10, 0x44, 0x10, 0x44, 0x08, 0x88, 0x07, 0xF0, 0x00, 0x00}, /*"9",25*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0C, 0x03, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*":",26*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*";",27*/
    {0x00, 0x00, 0x00, 0x80, 0x01, 0x40, 0x02, 0x20, 0x04, 0x10, 0x08, 0x08, 0x10, 0x04, 0x00, 0x00}, /*"<",28*/
    {0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x00, 0x00}, /*"=",29*/
    {0x00, 0x00, 0x10, 0x04, 0x08, 0x08, 0x04, 0x10, 0x02, 0x20, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00}, /*">",30*/
    {0x00, 0x00, 0x0E, 0x00, 0x12, 0x00, 0x10, 0x0C, 0x10, 0x6C, 0x10, 0x80, 0x0F, 0x00, 0x00, 0x00}, /*"?",31*/
    {0x03, 0xE0, 0x0C, 0x18, 0x13, 0xE4, 0x14, 0x24, 0x17, 0xC4, 0x08, 0x28, 0x07, 0xD0, 0x00, 0x00}, /*"@",32*/
    {0x00, 0x04, 0x00, 0x3C, 0x03, 0xC4, 0x1C, 0x40, 0x07, 0x40, 0x00, 0xE4, 0x00, 0x1C, 0x00, 0x04}, /*"A",33*/
    {0x10, 0x04, 0x1F, 0xFC, 0x11, 0x04, 0x11, 0x04, 0x11, 0x04, 0x0E, 0x88, 0x00, 0x70, 0x00, 0x00}, /*"B",34*/
    {0x03, 0xE0, 0x0C, 0x18, 0x10, 0x04, 0x10, 0x04, 0x10, 0x04, 0x10, 0x08, 0x1C, 0x10, 0x00, 0x00}, /*"C",35*/
    {0x10, 0x04, 0x1F, 0xFC, 0x10, 0x04, 0x10, 0x04, 0x10, 0x04, 0x08, 0x08, 0x07, 0xF0, 0x00, 0x00}, /*"D",36*/
    {0x10, 0x04, 0x1F, 0xFC, 0x11, 0x04, 0x11, 0x04, 0x17, 0xC4, 0x10, 0x04, 0x08, 0x18, 0x00, 0x00}, /*"E",37*/
    {0x10, 0x04, 0x1F, 0xFC, 0x11, 0x04, 0x11, 0x00, 0x17, 0xC0, 0x10, 0x00, 0x08, 0x00, 0x00, 0x00}, /*"F",38*/
    {0x03, 0xE0, 0x0C, 0x18, 0x10, 0x04, 0x10, 0x04, 0x10, 0x44, 0x1C, 0x78, 0x00, 0x40, 0x00, 0x00}, /*"G",39*/
    {0x10, 0x04, 0x1F, 0xFC, 0x10, 0x84, 0x00, 0x80, 0x00, 0x80, 0x10, 0x84, 0x1F, 0xFC, 0x10, 0x04}, /*"H",40*/
    {0x00, 0x00, 0x10, 0x04, 0x10, 0x04, 0x1F, 0xFC, 0x10, 0x04, 0x10, 0x04, 0x00, 0x00, 0x00, 0x00}, /*"I",41*/
    {0x00, 0x03, 0x00, 0x01, 0x10, 0x01, 0x10, 0x01, 0x1F, 0xFE, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00}, /*"J",42*/
    {0x10, 0x04, 0x1F, 0xFC, 0x11, 0x04, 0x03, 0x80, 0x14, 0x64, 0x18, 0x1C, 0x10, 0x04, 0x00, 0x00}, /*"K",43*/
    {0x10, 0x04, 0x1F, 0xFC, 0x10, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x0C, 0x00, 0x00}, /*"L",44*/
    {0x10, 0x04, 0x1F, 0xFC, 0x1F, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x1F, 0xFC, 0x10, 0x04, 0x00, 0x00}, /*"M",45*/
    {0x10, 0x04, 0x1F, 0xFC, 0x0C, 0x04, 0x03, 0x00, 0x00, 0xE0, 0x10, 0x18, 0x1F, 0xFC, 0x10, 0x00}, /*"N",46*/
    {0x07, 0xF0, 0x08, 0x08, 0x10, 0x04, 0x10, 0x04, 0x10, 0x04, 0x08, 0x08, 0x07, 0xF0, 0x00, 0x00}, /*"O",47*/
    {0x10, 0x04, 0x1F, 0xFC, 0x10, 0x84, 0x10, 0x80, 0x10, 0x80, 0x10, 0x80, 0x0F, 0x00, 0x00, 0x00}, /*"P",48*/
    {0x07, 0xF0, 0x08, 0x18, 0x10, 0x24, 0x10, 0x24, 0x10, 0x1C, 0x08, 0x0A, 0x07, 0xF2, 0x00, 0x00}, /*"Q",49*/
    {0x10, 0x04, 0x1F, 0xFC, 0x11, 0x04, 0x11, 0x00, 0x11, 0xC0, 0x11, 0x30, 0x0E, 0x0C, 0x00, 0x04}, /*"R",50*/
    {0x00, 0x00, 0x0E, 0x1C, 0x11, 0x04, 0x10, 0x84, 0x10, 0x84, 0x10, 0x44, 0x1C, 0x38, 0x00, 0x00}, /*"S",51*/
    {0x18, 0x00, 0x10, 0x00, 0x10, 0x04, 0x1F, 0xFC, 0x10, 0x04, 0x10, 0x00, 0x18, 0x00, 0x00, 0x00}, /*"T",52*/
    {0x10, 0x00, 0x1F, 0xF8, 0x10, 0x04, 0x00, 0x04, 0x00, 0x04, 0x10, 0x04, 0x1F, 0xF8, 0x10, 0x00}, /*"U",53*/
    {0x10, 0x00, 0x1E, 0x00, 0x11, 0xE0, 0x00, 0x1C, 0x00, 0x70, 0x13, 0x80, 0x1C, 0x00, 0x10, 0x00}, /*"V",54*/
    {0x1F, 0xC0, 0x10, 0x3C, 0x00, 0xE0, 0x1F, 0x00, 0x00, 0xE0, 0x10, 0x3C, 0x1F, 0xC0, 0x00, 0x00}, /*"W",55*/
    {0x10, 0x04, 0x18, 0x0C, 0x16, 0x34, 0x01, 0xC0, 0x01, 0xC0, 0x16, 0x34, 0x18, 0x0C, 0x10, 0x04}, /*"X",56*/
    {0x10, 0x00, 0x1C, 0x00, 0x13, 0x04, 0x00, 0xFC, 0x13, 0x04, 0x1C, 0x00, 0x10, 0x00, 0x00, 0x00}, /*"Y",57*/
    {0x08, 0x04, 0x10, 0x1C, 0x10, 0x64, 0x10, 0x84, 0x13, 0x04, 0x1C, 0x04, 0x10, 0x18, 0x00, 0x00}, /*"Z",58*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFE, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x00, 0x00}, /*"[",59*/
    {0x00, 0x00, 0x30, 0x00, 0x0C, 0x00, 0x03, 0x80, 0x00, 0x60, 0x00, 0x1C, 0x00, 0x03, 0x00, 0x00}, /*"\",60*/
    {0x00, 0x00, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x7F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"]",61*/
    {0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x20, 0x00, 0x00, 0x00}, /*"^",62*/
    {0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01}, /*"_",63*/
    {0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"`",64*/
    {0x00, 0x00, 0x00, 0x98, 0x01, 0x24, 0x01, 0x44, 0x01, 0x44, 0x01, 0x44, 0x00, 0xFC, 0x00, 0x04}, /*"a",65*/
    {0x10, 0x00, 0x1F, 0xFC, 0x00, 0x88, 0x01, 0x04, 0x01, 0x04, 0x00, 0x88, 0x00, 0x70, 0x00, 0x00}, /*"b",66*/
    {0x00, 0x00, 0x00, 0x70, 0x00, 0x88, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x00, 0x88, 0x00, 0x00}, /*"c",67*/
    {0x00, 0x00, 0x00, 0x70, 0x00, 0x88, 0x01, 0x04, 0x01, 0x04, 0x11, 0x08, 0x1F, 0xFC, 0x00, 0x04}, /*"d",68*/
    {0x00, 0x00, 0x00, 0xF8, 0x01, 0x44, 0x01, 0x44, 0x01, 0x44, 0x01, 0x44, 0x00, 0xC8, 0x00, 0x00}, /*"e",69*/
    {0x00, 0x00, 0x01, 0x04, 0x01, 0x04, 0x0F, 0xFC, 0x11, 0x04, 0x11, 0x04, 0x11, 0x00, 0x18, 0x00}, /*"f",70*/
    {0x00, 0x00, 0x00, 0xD6, 0x01, 0x29, 0x01, 0x29, 0x01, 0x29, 0x01, 0xC9, 0x01, 0x06, 0x00, 0x00}, /*"g",71*/
    {0x10, 0x04, 0x1F, 0xFC, 0x00, 0x84, 0x01, 0x00, 0x01, 0x00, 0x01, 0x04, 0x00, 0xFC, 0x00, 0x04}, /*"h",72*/
    {0x00, 0x00, 0x01, 0x04, 0x19, 0x04, 0x19, 0xFC, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00}, /*"i",73*/
    {0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x01, 0x01, 0x19, 0x01, 0x19, 0xFE, 0x00, 0x00, 0x00, 0x00}, /*"j",74*/
    {0x10, 0x04, 0x1F, 0xFC, 0x00, 0x24, 0x00, 0x40, 0x01, 0xB4, 0x01, 0x0C, 0x01, 0x04, 0x00, 0x00}, /*"k",75*/
    {0x00, 0x00, 0x10, 0x04, 0x10, 0x04, 0x1F, 0xFC, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00}, /*"l",76*/
    {0x01, 0x04, 0x01, 0xFC, 0x01, 0x04, 0x01, 0x00, 0x01, 0xFC, 0x01, 0x04, 0x01, 0x00, 0x00, 0xFC}, /*"m",77*/
    {0x01, 0x04, 0x01, 0xFC, 0x00, 0x84, 0x01, 0x00, 0x01, 0x00, 0x01, 0x04, 0x00, 0xFC, 0x00, 0x04}, /*"n",78*/
    {0x00, 0x00, 0x00, 0xF8, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x00, 0xF8, 0x00, 0x00}, /*"o",79*/
    {0x01, 0x01, 0x01, 0xFF, 0x00, 0x85, 0x01, 0x04, 0x01, 0x04, 0x00, 0x88, 0x00, 0x70, 0x00, 0x00}, /*"p",80*/
    {0x00, 0x00, 0x00, 0x70, 0x00, 0x88, 0x01, 0x04, 0x01, 0x04, 0x01, 0x05, 0x01, 0xFF, 0x00, 0x01}, /*"q",81*/
    {0x01, 0x04, 0x01, 0x04, 0x01, 0xFC, 0x00, 0x84, 0x01, 0x04, 0x01, 0x00, 0x01, 0x80, 0x00, 0x00}, /*"r",82*/
    {0x00, 0x00, 0x00, 0xCC, 0x01, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x98, 0x00, 0x00}, /*"s",83*/
    {0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x07, 0xF8, 0x01, 0x04, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00}, /*"t",84*/
    {0x01, 0x00, 0x01, 0xF8, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x01, 0x08, 0x01, 0xFC, 0x00, 0x04}, /*"u",85*/
    {0x01, 0x00, 0x01, 0x80, 0x01, 0x70, 0x00, 0x0C, 0x00, 0x10, 0x01, 0x60, 0x01, 0x80, 0x01, 0x00}, /*"v",86*/
    {0x01, 0xF0, 0x01, 0x0C, 0x00, 0x30, 0x01, 0xC0, 0x00, 0x30, 0x01, 0x0C, 0x01, 0xF0, 0x01, 0x00}, /*"w",87*/
    {0x00, 0x00, 0x01, 0x04, 0x01, 0x8C, 0x00, 0x74, 0x01, 0x70, 0x01, 0x8C, 0x01, 0x04, 0x00, 0x00}, /*"x",88*/
    {0x01, 0x01, 0x01, 0x81, 0x01, 0x71, 0x00, 0x0E, 0x00, 0x18, 0x01, 0x60, 0x01, 0x80, 0x01, 0x00}, /*"y",89*/
    {0x00, 0x00, 0x01, 0x84, 0x01, 0x0C, 0x01, 0x34, 0x01, 0x44, 0x01, 0x84, 0x01, 0x0C, 0x00, 0x00}, /*"z",90*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x3E, 0xFC, 0x40, 0x02, 0x40, 0x02}, /*"{",91*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"|",92*/
    {0x00, 0x00, 0x40, 0x02, 0x40, 0x02, 0x3E, 0xFC, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"}",93*/
    {0x00, 0x00, 0x60, 0x00, 0x80, 0x00, 0x80, 0x00, 0x40, 0x00, 0x40, 0x00, 0x20, 0x00, 0x20, 0x00}, /*"~",94*/
};

#endif // !MYTFT_H
