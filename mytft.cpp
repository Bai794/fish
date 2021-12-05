#include "mytft.h"
#include "stdlib.h"
#define LCD_SCL_Clr digitalWrite(LCD_SCL, LOW); //
#define LCD_SCL_Set digitalWrite(LCD_SCL, HIGH);

#define LCD_SDA_Clr digitalWrite(LCD_SDA, LOW); //
#define LCD_SDA_Set digitalWrite(LCD_SDA, HIGH);

#define LCD_RESET_Clr digitalWrite(LCD_RESET, LOW); //
#define LCD_RESET_Set digitalWrite(LCD_RESET, HIGH);

#define LCD_RS_Clr digitalWrite(LCD_RS, LOW); // DC
#define LCD_RS_Set digitalWrite(LCD_RS, HIGH);

#define LCD_CS_Clr digitalWrite(LCD_CS, LOW); // CS
#define LCD_CS_Set digitalWrite(LCD_CS, HIGH);

u8 DFT_SCAN_DIR;
//////////////////////////////////////////////////////////////////////////////////

// LCD�Ļ�����ɫ�ͱ���ɫ
u16 POINT_COLOR = 0x0000; //������ɫ
u16 BACK_COLOR = 0xFFFF;  //����ɫ

//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;

//д�Ĵ�������
// regval:�Ĵ���ֵ
void LCD_WR_REG(u8 REG)
{
  u8 i;
  LCD_CS_Clr;
  LCD_RS_Clr;
  for (i = 0; i < 8; i++)
  {
    if (REG & 0x80)
    {
      LCD_SDA_Set;
    }
    else
    {
      LCD_SDA_Clr;
    }
    REG <<= 1;
    LCD_SCL_Clr;
    LCD_SCL_Set;
  } //�͵�8λ
  LCD_CS_Set;
}
//дLCD����
// data:Ҫд���ֵ
void LCD_WR_DATA(u16 DATA)
{
  u8 i;
  LCD_CS_Clr;
  LCD_RS_Set;

  for (i = 0; i < 8; i++)
  {
    if (DATA & 0x80)
    {
      LCD_SDA_Set;
    }
    else
    {
      LCD_SDA_Clr;
    }
    DATA <<= 1;
    LCD_SCL_Clr;
    LCD_SCL_Set;
  } //�͵�8λ
  LCD_CS_Set;
}
//д�Ĵ���
// LCD_Reg:�Ĵ�����ַ
// LCD_RegValue:Ҫд�������
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{
  LCD_WR_REG(LCD_Reg);
  LCD_WR_DATA(LCD_RegValue);
}
//��ʼдGRAM
void LCD_WriteRAM_Prepare(void)
{
  LCD_WR_REG(lcddev.wramcmd);
}
// LCDдGRAM
// RGB_Code:��ɫֵ
void LCD_WriteRAM(u16 DAT)
{
  u8 i;
  LCD_CS_Clr;
  LCD_RS_Set;
  for (i = 0; i < 16; i++)
  {
    if (DAT & 0x8000)
    {
      LCD_SDA_Set;
    }
    else
    {
      LCD_SDA_Clr;
    }
    DAT <<= 1;
    LCD_SCL_Clr;
    LCD_SCL_Set;
  }
  LCD_CS_Set;
}

//��mdk -O1ʱ���Ż�ʱ��Ҫ����
//��ʱi
void opt_delay(u8 i)
{
  while (i--)
    ;
}

//���ù��λ��
// Xpos:������
// Ypos:������
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
  LCD_WR_REG(lcddev.setxcmd);
  LCD_WR_DATA(Xpos >> 8);
  LCD_WR_DATA(Xpos & 0XFF);

  LCD_WR_REG(lcddev.setycmd);
  LCD_WR_DATA(Ypos >> 8);
  LCD_WR_DATA(Ypos & 0XFF);
}
//����LCD���Զ�ɨ�跽��
//ע��:�����������ܻ��ܵ��˺������õ�Ӱ��(������9341/6804����������),
//����,һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.
// dir:0~7,����8������(���嶨���lcd.h)
// 9320/9325/9328/4531/4535/1505/b505/8989/5408/9341��IC�Ѿ�ʵ�ʲ���
void LCD_Scan_Dir(u8 dir)
{
  u16 regval = 0;
  u8 dirreg = 0;
  u16 temp;
  switch (dir) //����ת��
  {
  case 0:
    dir = 6;
    break;
  case 1:
    dir = 7;
    break;
  case 2:
    dir = 4;
    break;
  case 3:
    dir = 5;
    break;
  case 4:
    dir = 1;
    break;
  case 5:
    dir = 0;
    break;
  case 6:
    dir = 3;
    break;
  case 7:
    dir = 2;
    break;
  }
  switch (dir)
  {
  case L2R_U2D: //������,���ϵ���
    regval |= (0 << 7) | (0 << 6) | (0 << 5);
    break;
  case L2R_D2U: //������,���µ���
    regval |= (1 << 7) | (0 << 6) | (0 << 5);
    break;
  case R2L_U2D: //���ҵ���,���ϵ���
    regval |= (0 << 7) | (1 << 6) | (0 << 5);
    break;
  case R2L_D2U: //���ҵ���,���µ���
    regval |= (1 << 7) | (1 << 6) | (0 << 5);
    break;
  case U2D_L2R: //���ϵ���,������
    regval |= (0 << 7) | (0 << 6) | (1 << 5);
    break;
  case U2D_R2L: //���ϵ���,���ҵ���
    regval |= (0 << 7) | (1 << 6) | (1 << 5);
    break;
  case D2U_L2R: //���µ���,������
    regval |= (1 << 7) | (0 << 6) | (1 << 5);
    break;
  case D2U_R2L: //���µ���,���ҵ���
    regval |= (1 << 7) | (1 << 6) | (1 << 5);
    break;
  }
  dirreg = 0X36;
  regval |= 0x00;
  LCD_WriteReg(dirreg, regval);

  LCD_WR_REG(lcddev.setxcmd);
  LCD_WR_DATA(0);
  LCD_WR_DATA(0);
  LCD_WR_DATA((lcddev.width - 1) >> 8);
  LCD_WR_DATA((lcddev.width - 1) & 0XFF);
  LCD_WR_REG(lcddev.setycmd);
  LCD_WR_DATA(0);
  LCD_WR_DATA(0);
  LCD_WR_DATA((lcddev.height - 1) >> 8);
  LCD_WR_DATA((lcddev.height - 1) & 0XFF);
}
//����
// x,y:����
// POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x, u16 y)
{
  LCD_SetCursor(x, y);    //���ù��λ��
  LCD_WriteRAM_Prepare(); //��ʼд��GRAM

  LCD_WR_DATA(POINT_COLOR >> 8);
  LCD_WR_DATA(POINT_COLOR);
}

//����LCD��ʾ����6804��֧�ֺ�����ʾ��
// dir:0,������1,����
void LCD_Display_Dir(u8 dir)
{
  if (dir == 0) //����
  {
    lcddev.dir = 0; //����
    lcddev.width = 240;
    lcddev.height = 320;

    lcddev.wramcmd = 0X2C;
    lcddev.setxcmd = 0X2A;
    lcddev.setycmd = 0X2B;
    DFT_SCAN_DIR = U2D_R2L;
  }
  else //����
  {
    lcddev.dir = 1; //����
    lcddev.width = 320;
    lcddev.height = 240;

    lcddev.wramcmd = 0X2C;
    lcddev.setxcmd = 0X2A;
    lcddev.setycmd = 0X2B;
    DFT_SCAN_DIR = L2R_U2D;
  }
  LCD_Scan_Dir(DFT_SCAN_DIR); //Ĭ��ɨ�跽��
}
//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ILI93XXҺ��,�������������ǻ���ILI9320��!!!
//�������ͺŵ�����оƬ��û�в���!
void LCD_Init(void)
{

  // LCD��λ
  pinMode(LCD_RESET, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_SCL, OUTPUT);
  pinMode(LCD_SDA, OUTPUT);

  LCD_RESET_Set;
  delay(10);
  LCD_RESET_Clr;
  delay(80);
  LCD_RESET_Set;
  delay(10);

  //---------------------------------------------------------------------------------------------------//
  LCD_WR_REG(0x11);
  delay(220); // Delay 120ms
  //------------------------------display and color format setting--------------------------------//
  LCD_WR_REG(0x36);
  LCD_WR_DATA(0x00);
  LCD_WR_REG(0x3a);
  LCD_WR_DATA(0x05);
  //--------------------------------ST7789V Frame rate setting----------------------------------//
  LCD_WR_REG(0xb2);
  LCD_WR_DATA(0x0c);
  LCD_WR_DATA(0x0c);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x33);
  LCD_WR_DATA(0x33);
  LCD_WR_REG(0xb7);
  LCD_WR_DATA(0x35);
  //---------------------------------ST7789V Power setting--------------------------------------//
  LCD_WR_REG(0xbb);
  LCD_WR_DATA(0x28);
  LCD_WR_REG(0xc0);
  LCD_WR_DATA(0x2c);
  LCD_WR_REG(0xc2);
  LCD_WR_DATA(0x01);
  LCD_WR_REG(0xc3);
  LCD_WR_DATA(0x0b);
  LCD_WR_REG(0xc4);
  LCD_WR_DATA(0x20);
  LCD_WR_REG(0xc6);
  LCD_WR_DATA(0x0f);
  LCD_WR_REG(0xd0);
  LCD_WR_DATA(0xa4);
  LCD_WR_DATA(0xa1);
  //--------------------------------ST7789V gamma setting---------------------------------------//
  LCD_WR_REG(0xe0);
  LCD_WR_DATA(0xd0);
  LCD_WR_DATA(0x01);
  LCD_WR_DATA(0x08);
  LCD_WR_DATA(0x0f);
  LCD_WR_DATA(0x11);
  LCD_WR_DATA(0x2a);
  LCD_WR_DATA(0x36);
  LCD_WR_DATA(0x55);
  LCD_WR_DATA(0x44);
  LCD_WR_DATA(0x3a);
  LCD_WR_DATA(0x0b);
  LCD_WR_DATA(0x06);
  LCD_WR_DATA(0x11);
  LCD_WR_DATA(0x20);
  LCD_WR_REG(0xe1);
  LCD_WR_DATA(0xd0);
  LCD_WR_DATA(0x02);
  LCD_WR_DATA(0x07);
  LCD_WR_DATA(0x0a);
  LCD_WR_DATA(0x0b);
  LCD_WR_DATA(0x18);
  LCD_WR_DATA(0x34);
  LCD_WR_DATA(0x43);
  LCD_WR_DATA(0x4a);
  LCD_WR_DATA(0x2b);
  LCD_WR_DATA(0x1b);
  LCD_WR_DATA(0x1c);
  LCD_WR_DATA(0x22);
  LCD_WR_DATA(0x1f);
  LCD_WR_REG(0x29);

  LCD_Display_Dir(0); //Ĭ��Ϊ����   0����  1����
  LCD_Clear(WHITE);
}
//��������
// color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
  u32 index = 0;
  u32 totalpoint = lcddev.width;
  totalpoint *= lcddev.height; //�õ��ܵ���
  LCD_SetCursor(0x00, 0x0000); //���ù��λ��
  LCD_WriteRAM_Prepare();      //��ʼд��GRAM
  for (index = 0; index < totalpoint; index++)
  {
    LCD_WR_DATA(color >> 8);
    LCD_WR_DATA(color);
  }
}
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)
// color:Ҫ������ɫ
void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color)
{
  u16 i, j;
  u16 xlen = 0;
  xlen = ex - sx + 1;
  for (i = sy; i <= ey; i++)
  {
    LCD_SetCursor(sx, i);   //���ù��λ��
    LCD_WriteRAM_Prepare(); //��ʼд��GRAM
    for (j = 0; j < xlen; j++)
      LCD_WriteRAM(color); //���ù��λ��
  }
}
//��ָ�����������ָ����ɫ��
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)
// color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 *color)
{
  u16 height, width;
  u16 i, j;
  width = ex - sx + 1;  //�õ����Ŀ��
  height = ey - sy + 1; //�߶�
  for (i = 0; i < height; i++)
  {
    LCD_SetCursor(sx, sy + i); //���ù��λ��
    LCD_WriteRAM_Prepare();    //��ʼд��GRAM
    for (j = 0; j < width; j++)
      LCD_WriteRAM(color[i * height + j]); //д������
  }
}
//����
// x1,y1:�������
// x2,y2:�յ�����
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
  u16 t;
  int xerr = 0, yerr = 0, delta_x, delta_y, distance;
  int incx, incy, uRow, uCol;
  delta_x = x2 - x1; //������������
  delta_y = y2 - y1;
  uRow = x1;
  uCol = y1;
  if (delta_x > 0)
    incx = 1; //���õ�������
  else if (delta_x == 0)
    incx = 0; //��ֱ��
  else
  {
    incx = -1;
    delta_x = -delta_x;
  }
  if (delta_y > 0)
    incy = 1;
  else if (delta_y == 0)
    incy = 0; //ˮƽ��
  else
  {
    incy = -1;
    delta_y = -delta_y;
  }
  if (delta_x > delta_y)
    distance = delta_x; //ѡȡ��������������
  else
    distance = delta_y;
  for (t = 0; t <= distance + 1; t++) //�������
  {
    LCD_DrawPoint(uRow, uCol); //����
    xerr += delta_x;
    yerr += delta_y;
    if (xerr > distance)
    {
      xerr -= distance;
      uRow += incx;
    }
    if (yerr > distance)
    {
      yerr -= distance;
      uCol += incy;
    }
  }
}
//������
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
  LCD_DrawLine(x1, y1, x2, y1);
  LCD_DrawLine(x1, y1, x1, y2);
  LCD_DrawLine(x1, y2, x2, y2);
  LCD_DrawLine(x2, y1, x2, y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
// r    :�뾶
void Draw_Circle(u16 x0, u16 y0, u8 r)
{
  int a, b;
  int di;
  a = 0;
  b = r;
  di = 3 - (r << 1); //�ж��¸���λ�õı�־
  while (a <= b)
  {
    LCD_DrawPoint(x0 + a, y0 - b); // 5
    LCD_DrawPoint(x0 + b, y0 - a); // 0
    LCD_DrawPoint(x0 + b, y0 + a); // 4
    LCD_DrawPoint(x0 + a, y0 + b); // 6
    LCD_DrawPoint(x0 - a, y0 + b); // 1
    LCD_DrawPoint(x0 - b, y0 + a);
    LCD_DrawPoint(x0 - a, y0 - b); // 2
    LCD_DrawPoint(x0 - b, y0 - a); // 7
    a++;
    //ʹ��Bresenham�㷨��Բ
    if (di < 0)
      di += 4 * a + 6;
    else
    {
      di += 10 + 4 * (a - b);
      b--;
    }
  }
}
//��ָ��λ����ʾһ���ַ�
// x,y:��ʼ����
// num:Ҫ��ʾ���ַ�:" "--->"~"
// size:�����С 12/16
// mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 size, u8 mode)
{
  u8 temp, t1, t;
  u16 y0 = y;
  u16 colortemp = POINT_COLOR;
  //���ô���
  num = num - ' '; //�õ�ƫ�ƺ��ֵ
  if (!mode)       //�ǵ��ӷ�ʽ
  {
    for (t = 0; t < size; t++)
    {
      if (size == 12)
        temp = asc2_1206[num][t]; //����1206����
      else
        temp = asc2_1608[num][t]; //����1608����
      for (t1 = 0; t1 < 8; t1++)
      {
        if (temp & 0x80)
          POINT_COLOR = colortemp;
        else
          POINT_COLOR = BACK_COLOR;
        LCD_DrawPoint(x, y);
        temp <<= 1;
        y++;
        if (x >= lcddev.width)
        {
          POINT_COLOR = colortemp;
          return;
        } //��������
        if ((y - y0) == size)
        {
          y = y0;
          x++;
          if (x >= lcddev.width)
          {
            POINT_COLOR = colortemp;
            return;
          } //��������
          break;
        }
      }
    }
  }
  else //���ӷ�ʽ
  {
    for (t = 0; t < size; t++)
    {
      if (size == 12)
        temp = asc2_1206[num][t]; //����1206����
      else
        temp = asc2_1608[num][t]; //����1608����
      for (t1 = 0; t1 < 8; t1++)
      {
        if (temp & 0x80)
          LCD_DrawPoint(x, y);
        temp <<= 1;
        y++;
        if (x >= lcddev.height)
        {
          POINT_COLOR = colortemp;
          return;
        } //��������
        if ((y - y0) == size)
        {
          y = y0;
          x++;
          if (x >= lcddev.width)
          {
            POINT_COLOR = colortemp;
            return;
          } //��������
          break;
        }
      }
    }
  }
  POINT_COLOR = colortemp;
}
// m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m, u8 n)
{
  u32 result = 1;
  while (n--)
    result *= m;
  return result;
}
//��ʾ����,��λΪ0,����ʾ
// x,y :�������
// len :���ֵ�λ��
// size:�����С
// color:��ɫ
// num:��ֵ(0~4294967295);
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size)
{
  u8 t, temp;
  u8 enshow = 0;
  for (t = 0; t < len; t++)
  {
    temp = (num / LCD_Pow(10, len - t - 1)) % 10;
    if (enshow == 0 && t < (len - 1))
    {
      if (temp == 0)
      {
        LCD_ShowChar(x + (size / 2) * t, y, ' ', size, 0);
        continue;
      }
      else
        enshow = 1;
    }
    LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, 0);
  }
}
//��ʾ����,��λΪ0,������ʾ
// x,y:�������
// num:��ֵ(0~999999999);
// len:����(��Ҫ��ʾ��λ��)
// size:�����С
// mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x, u16 y, u32 num, u8 len, u8 size, u8 mode)
{
  u8 t, temp;
  u8 enshow = 0;
  for (t = 0; t < len; t++)
  {
    temp = (num / LCD_Pow(10, len - t - 1)) % 10;
    if (enshow == 0 && t < (len - 1))
    {
      if (temp == 0)
      {
        if (mode & 0X80)
          LCD_ShowChar(x + (size / 2) * t, y, '0', size, mode & 0X01);
        else
          LCD_ShowChar(x + (size / 2) * t, y, ' ', size, mode & 0X01);
        continue;
      }
      else
        enshow = 1;
    }
    LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, mode & 0X01);
  }
}
//��ʾ�ַ���
// x,y:�������
// width,height:�����С
// size:�����С
//*p:�ַ�����ʼ��ַ
void LCD_ShowString(u16 x, u16 y, u16 width, u16 height, u8 size, const char *ptr)
{
  u8 x0 = x;
  const char *p;
  p = &ptr[0];
  width += x;
  height += y;
  while ((*p <= '~') && (*p >= ' ')) //�ж��ǲ��ǷǷ��ַ�!
  {
    if (x >= width)
    {
      x = x0;
      y += size;
    }
    if (y >= height)
      break; //�˳�
    LCD_ShowChar(x, y, *p, size, 0);
    x += size / 2;
    p++;
  }
}

//���ô���
void LCD_Set_Window(u16 sx, u16 sy, u16 width, u16 height)
{
  width = sx + width - 1;
  height = sy + height - 1;

  LCD_WR_REG(lcddev.setxcmd);
  LCD_WR_DATA(sx >> 8);
  LCD_WR_DATA(sx & 0XFF);
  LCD_WR_DATA(width >> 8);
  LCD_WR_DATA(width & 0XFF);
  LCD_WR_REG(lcddev.setycmd);
  LCD_WR_DATA(sy >> 8);
  LCD_WR_DATA(sy & 0XFF);
  LCD_WR_DATA(height >> 8);
  LCD_WR_DATA(height & 0XFF);
}