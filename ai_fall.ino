#include <LiquidCrystal.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;
int xval,yval,zval,magnitude;

#define buz 5


const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int cnt=0;
#define ec1 7
#define tr1 6
int sts=0;



void setup() {
  
  Serial.begin(9600); 
  pinMode(buz,OUTPUT);
 
  digitalWrite(buz,0);
  lcd.begin(16, 2);
  lcd.print("   WELCOME");
  delay(1000);
 
pinMode(tr1,OUTPUT);
pinMode(ec1,INPUT);

  digitalWrite(buz,0);
  mpu.begin();
}

void loop() {


digitalWrite(tr1,0);
delayMicroseconds(2);
digitalWrite(tr1,1);
delayMicroseconds(10);
int dst1=pulseIn(ec1,1)/58.2;

 sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  xval= a.acceleration.x;
  yval= a.acceleration.y;
  zval= a.acceleration.z;
 if(xval < -5 || xval>5 || yval<-5 || yval>5)
 {
  digitalWrite(buz,1);
 }
 else
 {
  digitalWrite(buz,0);
 }
Serial.print(String(xval)+","+String(yval)+ ","+String(zval)+ ","+String(dst1)+",0\n");
lcd.clear();
lcd.print("X:"+String(xval)+ " Y:"+String(yval) + " D:"+String(dst1));
delay(1000);
if(Serial.available())
{
  int x=Serial.read();
  if(x=='1')
  {
    lcd.setCursor(0,1);
    lcd.print("FALL DETECTED");
    digitalWrite(buz,1);
    while(1);

  }
}
}


 
