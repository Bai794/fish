/*
   @Author: HideMe
   @Date: 2021-10-31 22:04:43
 * @LastEditTime: 2021-11-30 12:11:07
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

AsyncWebServer server(80); //
float RedPh_value();
String mytime = "set 21 11 27 6 19 32"; //To Set The Time As 2008-8-8 Monday 12:00
void setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.begin(115200);                    //
  stepper1.setReductionRatio(1, 200 * 16); //
  stepper2.setReductionRatio(1, 200 * 16);
  stepper3.setReductionRatio(1, 200 * 16);

  Pin_init(); //
  ledcSetup(moter1, freq_PWM, resolution_PWM);
  ledcSetup(moter2, freq_PWM, resolution_PWM);
  ledcAttachPin(pwma, moter1);
  ledcAttachPin(pwmb, moter2);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "ip �����һ��??/update ��ʵ��ota����"); });

  AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");

  DS1302_Init();
  // Set_Time(mytime);
  Display_RTCC();
  tft.init(240, 240); //
  tft.fillScreen(BLUE);
  tft.drawPixel(tft.width() / 2, tft.height() / 2, GREEN);
}
void loop()
{

  AsyncElegantOTA.loop();
  Serial.println("hello baiyong");
  //  stepper1.stepnum_turns(3);
  //  stepper2.stepnum_turns(3);
  //  stepper3.stepnum_turns(3);
  //  stepper1.update();
  //  stepper2.update();
  //  stepper3.update();
  testroundrects();
  Display_RTCC();
  int num = key_scan();
  Serial.println(num);
  float ph_val = RedPh_value();
  Serial.print("ph_val:");
  Serial.println(ph_val);
  delay(500);
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
  for (int i = 0; i < 9; i++) //sort the analog from small to large
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
  for (int i = 2; i < 8; i++) //take the average value of 6 center sample
    avgValue += buf[i];
  float phValue = (float)avgValue * 3.3 / 4096 / 6;
  phValue = 3.5 * phValue + Offset;
  return phValue;
}
/**
   @description: ����������ˮ���??
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
