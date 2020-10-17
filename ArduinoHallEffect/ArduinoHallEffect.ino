/*
Arduino Hall Effect Sensor Project
by Arvind Sanjeev
Please check out  http://diyhacking.com for the tutorial of this project.
DIY Hacking
*/

#include <stdio.h>
 volatile byte half_revolutions;
 unsigned int rpm;
 unsigned long timeold;
 unsigned int num;
 void setup()
 {
   Serial.begin(115200);
   while (! Serial);
   Serial.println("\n\n\n New Start!!!");
   pinMode(2, INPUT_PULLUP);
   attachInterrupt(0, magnet_detect, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)
   half_revolutions = 0;
   rpm = 0;
   timeold = 0;
   num = 0;
   //delay(10);
 }
 
 void loop()//Measure RPM
 {
  
   if (half_revolutions >= 20) { 
     rpm = 30*1000/(millis() - timeold)*half_revolutions;
     timeold = millis();
     half_revolutions = 0;
     delay(500);
     Serial.println(rpm,DEC);
     
   }
 }
 
 void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
 {
   half_revolutions++;
   
   if((half_revolutions % 2) == 1){
    num ++;
   }

   
   //Serial.begin(115200);
   while (! Serial);
   Serial.print("half_revolution: ");
   Serial.print(half_revolutions);
   Serial.print("  num: ");
   Serial.println(num);
   
 }
