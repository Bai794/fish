#include "DS1302.h"
#include "Arduino.h"
SYSTEMTIME DS1302Buffer;
bool Flag_Time_Refresh = 1;

//****************************************************
//实时时钟写入一字节(内部函数)
//****************************************************
void DS1302_InputByte(unsigned char dat)    
{ 
    unsigned char i;

    pinMode(DS1302_IO,OUTPUT);

    for(i=0; i<8; i++)
    {
        if((dat & 0x01) == 1)
        {
            DS1302_IO_1;
        }
        else
        {
            DS1302_IO_0;
        }
          
        
        DS1302_CLK_0;               //上升沿写入数据
        
        delayMicroseconds(2);
        
        DS1302_CLK_1;
        
        delayMicroseconds(2);
        dat >>= 1; 
    } 
}

//****************************************************
//实时时钟读取一字节(内部函数)
//****************************************************
unsigned char DS1302_OutputByte(void)   
{ 
    unsigned char i;
    unsigned char dat;
    pinMode(DS1302_IO,INPUT);
    for(i=0; i<8; i++)
    {
        DS1302_CLK_1;                   //下降沿读出数据
        delayMicroseconds(2);
        DS1302_CLK_0;
        delayMicroseconds(2);
        dat >>= 1;                  
        if( digitalRead(DS1302_IO) == HIGH )
            dat |= 0x80;                //最高位置一
        else
            dat &= 0x7F;                //最高位清零       
    } 
    return(dat); 
}

//****************************************************
//ucAddr: DS1302地址, ucData: 要写的数据
//****************************************************
void DS1302_Write(unsigned char ucAddr, unsigned char ucDa) 
{
    DS1302_RST_0;
    delayMicroseconds(2);
    DS1302_CLK_0;
    delayMicroseconds(2);
    DS1302_RST_1;
    delayMicroseconds(2);
    DS1302_InputByte(ucAddr);           // 地址，命令 
    DS1302_InputByte(ucDa);             // 写1Byte数据
    DS1302_CLK_1;
    delayMicroseconds(2);
    DS1302_RST_0;
    delayMicroseconds(2);
}

//****************************************************
//读取DS1302某地址的数据
//****************************************************
unsigned char DS1302_Read(unsigned char ucAddr) 
{
    unsigned char ucData;
    DS1302_RST_0;
    delayMicroseconds(2);
    DS1302_CLK_0;
    delayMicroseconds(2);
    DS1302_RST_1;
    delayMicroseconds(2);
    DS1302_InputByte(ucAddr|0x01);        // 地址，命令 
    ucData = DS1302_OutputByte();         // 读1Byte数据
    DS1302_CLK_1;
    delayMicroseconds(2);
    DS1302_RST_0;
    delayMicroseconds(2);
    return(ucData);
}

//****************************************************
//是否写保护
//****************************************************
void DS1302_SetProtect(unsigned char flag)       
{
    if(flag)
        DS1302_Write(0x8E,0x10);            //保护
    else
        DS1302_Write(0x8E,0x00);            //不保护
} 

//****************************************************
// 设置时间函数
//****************************************************
void DS1302_SetTime(unsigned char Address, unsigned char Value)        
{
    DS1302_SetProtect(0);
    DS1302_Write(Address, ((Value/10)<<4 | (Value%10))); 
}

//****************************************************
//获取实时时间
//****************************************************

void DS1302_GetTime(SYSTEMTIME *Time)
{
    unsigned char ReadValue;
    ReadValue = DS1302_Read(DS1302_SECOND);
    ReadValue = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);            //BCD码转换十进制
    if(ReadValue != DS1302Buffer.Second)                                //跟上一次状态不同，置位刷新标志位
        Flag_Time_Refresh = 1;
    Time->Second = ReadValue;

    ReadValue = DS1302_Read(DS1302_MINUTE);
    Time->Minute = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
    ReadValue = DS1302_Read(DS1302_HOUR);
    Time->Hour = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
    ReadValue = DS1302_Read(DS1302_DAY);
    Time->Day = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);    
    ReadValue = DS1302_Read(DS1302_WEEK);
    Time->Week = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
    ReadValue = DS1302_Read(DS1302_MONTH);
    Time->Month = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
    ReadValue = DS1302_Read(DS1302_YEAR);
    Time->Year = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);   
}

//****************************************************
//初始化
//****************************************************
void DS1302_Init(void)
{
    unsigned char Second;

    pinMode(DS1302_RST,OUTPUT);
    pinMode(DS1302_IO,OUTPUT);
    pinMode(DS1302_CLK,OUTPUT);

    Second = DS1302_Read(DS1302_SECOND);
    if(Second&0x80)       
        DS1302_SetTime(DS1302_SECOND,Second & 0x7f);    //开启振荡    
}
//****************************************************
//DS1302振荡器停止
//****************************************************
void DS1302_ON_OFF(bool FLAG_ON_OFF)
{
    unsigned char Second;
    Second = DS1302_Read(DS1302_SECOND);
    if(FLAG_ON_OFF == 0)
        DS1302_Write(DS1302_SECOND,Second | 0x80);              //关闭振荡
    else
        DS1302_Write(DS1302_SECOND,Second & 0x7f);              //开启振荡
}
/*** 
 * @description: 
 * @function: 打印时间 默认使用串口0
 * @param {void}
 * @return {voif}
 */
void Display_RTCC()
{
  DS1302_GetTime(&DS1302Buffer);
  if (DS1302Buffer.Year < 10)
  {
    Serial.print("200"); //2000年开始
  }
  else
  {
    Serial.print("20");
  }
  Serial.print(DS1302Buffer.Year);
  Serial.print('-');
  Serial.print(DS1302Buffer.Month);
  Serial.print('-');
  Serial.print(DS1302Buffer.Day);

  Serial.print("   ");

  switch (DS1302Buffer.Week)
  {
    case 1:
      Serial.println("Mon");         //显示星期一
      break;
    case 2:
      Serial.println("Tue");         //显示星期二
      break;
    case 3:
      Serial.println("Wed");         //显示星期三
      break;
    case 4:
      Serial.println("Thu");         //显示星期四
      break;
    case 5:
      Serial.println("Fri");         //显示星期五
      break;
    case 6:
      Serial.println("Sat");         //显示星期六
      break;
    case 7:
      Serial.println("Sun");         //显示星期日
      break;
    default : break;
  }

  Serial.print(DS1302Buffer.Hour);
  Serial.print(':');
  Serial.print(DS1302Buffer.Minute);
  Serial.print(':');
  Serial.println(DS1302Buffer.Second);
}
/*** 
 * @description: 当string 为"set 08 08 08 1 12 00"  To Set The Time As 2008-8-8 Monday 12:00
 * @function: 修改内部ds1302的时间
 * @param {为sring 类型的command}
 * @return {无}
 */
void Set_Time(String &command)
{
  DS1302_ON_OFF(0);     //关闭振荡
  DS1302Buffer.Year = command.substring(4, 6).toInt();
  DS1302Buffer.Month = command.substring(7, 9).toInt();
  DS1302Buffer.Day = command.substring(10, 12).toInt();
  DS1302Buffer.Week = command.substring(13, 14).toInt();
  DS1302Buffer.Hour = command.substring(15, 17).toInt();
  DS1302Buffer.Minute = command.substring(18).toInt();
  DS1302_SetTime( DS1302_YEAR , DS1302Buffer.Year );
  DS1302_SetTime( DS1302_MONTH , DS1302Buffer.Month );
  DS1302_SetTime( DS1302_DAY , DS1302Buffer.Day );
  DS1302_SetTime( DS1302_WEEK , DS1302Buffer.Week );
  DS1302_SetTime( DS1302_HOUR , DS1302Buffer.Hour );
  DS1302_SetTime( DS1302_MINUTE , DS1302Buffer.Minute );
  DS1302_ON_OFF(1);
  Serial.println("Set Done");
  Display_RTCC();
}
