/*
   @Author: HideMe
   @Date: 2021-10-31 22:04:43
 * @LastEditTime: 2021-12-05 15:50:42
 * @LastEditors: your name
   @Description:
 * @FilePath: \fish\fish.ino
   @e-mail: 1269724114@qq.com
*/
#include <Arduino.h>
#include "DS1302.h"
#include "mystepper.h"
#include "pin.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "key.h"
#include "mytft.h"
#include "pid.h"
#include "control.h"

const char *ssid = "bai";           //
const char *password = "123456bai"; //

#define moter1 3
#define moter2 4
#define Offset 0.00
int freq_PWM = 50;
int resolution_PWM = 10;

extern SYSTEMTIME DS1302Buffer; //
mystepper stepper1(step1, dir1);
mystepper stepper2(step2, dir2);
mystepper stepper3(step3, dir3);
String comand, wificomand;
AsyncWebServer server(80); //

float RedPh_value();
void SmartConfig();
bool AutoConfig();
String mytime = "set 21 11 27 6 19 32"; // To Set The Time As 2008-8-8 Monday 12:00
float num = 0, num1 = 0;
void setup()
{

  Serial.begin(115200);                    //
  stepper1.setReductionRatio(1, 200 * 16); //
  stepper2.setReductionRatio(1, 200 * 16);
  stepper3.setReductionRatio(1, 200 * 16);
  Pin_init(); //
  LCD_Init();
  ledcSetup(moter1, freq_PWM, resolution_PWM);
  ledcSetup(moter2, freq_PWM, resolution_PWM);
  ledcAttachPin(pwma, moter1);
  ledcAttachPin(pwmb, moter2);
  LCD_Init();
  LCD_Init();
  LCD_Clear(WHITE);
  if (!AutoConfig())
  {
    SmartConfig();
  }
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "ip +/update"); });

  AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");

  DS1302_Init();
  // Set_Time(mytime);
  Display_RTCC();
}
void loop()
{

  while (Serial.available())
  {
    comand += char(Serial.read());
    delay(2);
  }
  if (comand.length() > 0)
  {
    num = comand.toFloat();
    comand = "";
    Serial.println(num);
    stepper2.stepnum_turns(num);
    stepper2.update();
  }
  //  AsyncElegantOTA.loop();
  if (num1 != num)
  {
    char buffer[10];
    sprintf(buffer, "%0.2f", num);
    LCD_ShowString(30, 70, 200, 16, 16, buffer);
    POINT_COLOR = RED;
    Draw_Circle(120, 120, 30);
  }
  uint8_t key_num = key_scan();
  if (key_num)
  {
    char buffer2[10];
    sprintf(buffer2, "key:%d", key_num);
    LCD_ShowString(30, 120, 240, 16, 16, buffer2);
  }
}
/**
   @description: ��ȡPHֵ
   @function:
   @param {*}
   @return {*}
*/
float RedPh_value()
{
  int buf[10], temp;
  unsigned long int avgValue = 0;
  for (int i = 0; i < 10; i++)
  {
    buf[i] = analogRead(ph);
  }
  for (int i = 0; i < 9; i++) // sort the analog from small to large
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  for (int i = 2; i < 8; i++) // take the average value of 6 center sample
    avgValue += buf[i];
  float phValue = (float)avgValue * 3.3 / 4096 / 6;
  phValue = 3.5 * phValue + Offset;
  return phValue;
}
/**
   @description:
   @function:
   @param {int} M
   @param {int} speed
   @return {*}
*/
void set_moterSpeed(int M, int speed)
{
  if (M == 1)
  {
    ledcWrite(moter1, speed);
  }
  else if (M == 2)
  {

    ledcWrite(moter2, speed);
  }
  return;
}

int key_scan()
{
  int a[6] = {sw1, sw2, sw3, sw4, sw5, sw6};
  for (int i = 0; i < 6; i++)
  {
    if (digitalRead(a[i]) == 0)
    {
      return i + 1;
    }
    else
      continue;
  }
  return 0;
}
void tft_show()
{
}
bool AutoConfig()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  //如果觉得时间太长可改
  for (int i = 0; i < 10; i++)
  {
    int wstatus = WiFi.status();
    if (wstatus == WL_CONNECTED)
    {
      LCD_Clear(WHITE);
      LCD_ShowString(0, 0, 240, 16, 16, "WIFI Success");
      String ip_str = "ssid:" + String(ssid) + "  IP:" + WiFi.localIP().toString();
      LCD_ShowString(0, 18, 240, 16, 16, ip_str.c_str()); //显示Ip
      return true;
    }
    else
    {
      LCD_ShowString(0, 0, 240, 16, 16, "WIFI AutoConfig Waiting..");
      delay(1000);
    }
  }
  LCD_ShowString(0, 0, 240, 16, 16, "WIFI AutoConfig Faild!");
  delay(500);
  return false;
}
void SmartConfig()
{
  WiFi.mode(WIFI_STA);
  WiFi.beginSmartConfig();
  LCD_Clear(WHITE);
  LCD_ShowString(0, 0, 240, 16, 16, "wait for smartconfig..");
  while (1)
  {
    Serial.print(".");
    delay(500);
    if (WiFi.smartConfigDone())
    {
      LCD_Clear(WHITE);
      LCD_ShowString(0, 0, 240, 16, 16, "Smartconfig WIFI Success");
      String ip_str = "ssid:" + WiFi.SSID() + " IP:" + WiFi.localIP().toString();
      LCD_ShowString(0, 18, 240, 16, 16, ip_str.c_str()); //显示Ip
      break;
    }
  }
}