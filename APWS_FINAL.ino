#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
const int moistureLevelSensor=A0;
int moistureLevel;
int count=0;
int Hour;
float Time;
int Sec;
int Min;
String dateTime;
String currentTime;
String currentDate;
BlynkTimer timer;
WidgetRTC rtc;
char auth[] = "Qi2DIH1ZqQD1vmQAg6B6gbEKzdfr0DBY";
char ssid[] = "Rajan";
char pass[] = "Rajan700852";
BLYNK_CONNECTED()
{
  rtc.begin();
}
void sendSensor2()
{
  moistureLevel=analogRead(moistureLevelSensor);
  moistureLevel=map(moistureLevel,732,250,0,100);
  currentTime=String(hour())+ ":" + minute() + ":" + second();
  currentDate=String(day()) + " | " + month() + " | " + year();
  if (moistureLevel<45)
  {
    digitalWrite(5,LOW);
    Blynk.virtualWrite(V8,"PUMP IS WORKING!");
    Blynk.virtualWrite(V1,currentTime,"---",currentDate);
    count=count+1;
    delay(3000);
  }
  else
  {
    digitalWrite(5,HIGH);
    Blynk.virtualWrite(V8,"PUMP IS NOT WORKING!");
  }
  Hour=hour();
  Min=minute();
  Sec=second();
  Time=(count*10)/60 ;
  if (Hour==0 && Min==0)
  {
    Blynk.virtualWrite(V2,Time," minutes");
  }
  
  Blynk.virtualWrite(V3,count);
  Blynk.virtualWrite(V4,moistureLevel);
}
void setup()
{
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L,sendSensor2);
  pinMode(5,OUTPUT);
  pinMode(A0,INPUT);
  
  
}

void loop()
{
  Blynk.run();
  timer.run();
  
  
 
  
}
