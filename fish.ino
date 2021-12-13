/*
   @Author: HideMe
   @Date: 2021-10-31 22:04:43
 * @LastEditTime: 2021-12-13 16:00:31
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

String comand, wificomand;
AsyncWebServer server(80); //
tm *tt;                    // ntp鑾峰彇缃戠粶鏃堕棿
unsigned long time_flag = 0;
float RedPh_value();
void SmartConfig();
bool AutoConfig();
void handle_key(int key_num);
extern float user_tagart, user_Nahco3, set_ph, run_Scale ; // 鐢ㄦ埛璁惧畾鐨勯奔姹犻噷姘磏ahco3娴撳害
String mytime = "set 21 11 27 6 19 32";        // To Set The Time As 2008-8-8 Monday 12:00


void setup()
{

  Serial.begin(115200);                    //
  step_init();
  Pin_init(); //
  LCD_Init();
  ledcSetup(moter1, freq_PWM, resolution_PWM);
  ledcSetup(moter2, freq_PWM, resolution_PWM);
  ledcAttachPin(pwma, moter1);
  ledcAttachPin(pwmb, moter2);
  LCD_Init();
  LCD_Init();
  LCD_Clear(BLACK);
  DS1302_Init();
  POINT_COLOR = WHITE;
  if (!AutoConfig())
  {
    SmartConfig();
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    tt = connectNTP();
    Set_Time(tt);
    String data = asctime(tt);
    Serial.println(data);
  }
  delay(100);
  LCD_ShowString(0, 0, 240, 16, 16, "fail received net time");
  if (tt != NULL)
  {
    LCD_Fill(0, 0, 239, 16, BLACK);
    LCD_ShowString(0, 0, 240, 16, 16, "Success received net time");
  }
  else
  {
    LCD_Fill(0, 0, 239, 16, BLACK);
    LCD_ShowString(0, 0, 240, 16, 16, "fail received net time");
  }
  LCD_ShowString(0, 36, 240, 16, 16, "time:");
  if (WiFi.status() == WL_CONNECTED)
  {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
    {
      request->send(200, "text/plain", "ip +/update");
    });
    AsyncElegantOTA.begin(&server); // Start ElegantOTA
    Serial.println("HTTP server started");
    server.begin();
  }
  else {
    LCD_ShowString(0, 18, 240, 16, 16, "WIFI failed");
  }
  Display_RTCC();
  tft_satrt();
  time_flag = millis();
}
void loop()
{
  if (millis() - time_flag > 1000)
  {
    time_flag = millis();
    DS1302_GetTime(&DS1302Buffer);
    tft_show();
  }
  while (Serial.available())
  {
    comand += char(Serial.read());
    delay(2);
  }
  if (comand.length() > 0)
  {
    float num = comand.toFloat();
    comand = "";
    Serial.println(num);
    run_step(2, num);
  }
  //  AsyncElegantOTA.loop();
  uint8_t key_num = key_scan();
  if (key_num)
  {
    handle_key(key_num);
    char buffer2[10];
    sprintf(buffer2, "key:%d", key_num);
    LCD_ShowString(30, 120, 240, 16, 16, buffer2);
  }
}
/**
   @description: 锟斤拷取PH值
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
      delay(100);
      if (digitalRead(a[i]) == 0)
        return i + 1;
      else continue;
    }
    else
      continue;
  }
  return 0;
}

bool AutoConfig()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  //濡傛灉瑙夊緱鏃堕棿澶暱鍙敼
  for (int i = 0; i < 10; i++)
  {
    int wstatus = WiFi.status();
    if (wstatus == WL_CONNECTED)
    {
      LCD_Clear(BLACK);
      LCD_ShowString(0, 0, 240, 16, 16, "WIFI Success");
      String ip_str = "ssid:" + String(ssid) + "  IP:" + WiFi.localIP().toString();
      LCD_ShowString(0, 18, 240, 16, 16, ip_str.c_str()); //鏄剧ずIp
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
  LCD_Clear(BLACK);
  LCD_ShowString(0, 0, 240, 16, 16, "wait for smartconfig..");
  for (int i = 0; i < 20; i++)
  {
    Serial.print(".");
    delay(500);
    if (WiFi.smartConfigDone())
    {
      LCD_Clear(BLACK);
      LCD_ShowString(0, 0, 240, 16, 16, "Smartconfig WIFI Success");
      String ip_str = "ssid:" + WiFi.SSID() + " IP:" + WiFi.localIP().toString();
      LCD_ShowString(0, 18, 240, 16, 16, ip_str.c_str()); //鏄剧ずIp
      break;
    }
  }
}
void handle_key(int key_num)
{
  if (key_num == 1)
  {
    user_tagart += 0.1;
    LCD_ShowString(160, 54, 240, 16, 16, String(user_tagart).c_str());
  }
  else if (key_num == 5)
  {
    user_tagart -= 0.1;
    LCD_ShowString(160, 54, 240, 16, 16, String(user_tagart).c_str());
  }
  else if (key_num == 3)
  {
    user_Nahco3 += 10;
    LCD_ShowString(50, 72, 240, 16, 16, String(user_Nahco3).c_str());
  }
  else if (key_num == 4)
  {
    user_Nahco3 -= 10;
    LCD_ShowString(50, 72, 240, 16, 16, String(user_Nahco3).c_str());
  }
  else if (key_num == 6)
  {
    run_Scale += 0.01;
    LCD_ShowString(160, 72, 240, 16, 16, String(run_Scale).c_str());
  }
  else if (key_num == 2)
  {
    run_Scale -= 0.01;
    LCD_ShowString(160, 72, 240, 16, 16, String(run_Scale).c_str());
  }
  else
    return;
}
