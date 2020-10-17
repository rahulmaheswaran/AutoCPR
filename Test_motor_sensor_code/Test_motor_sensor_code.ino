#include "DualG2HighPowerMotorShield.h"

DualG2HighPowerMotorShield24v14 md;
 volatile byte half_revolutions; //every time the sensor sense the magnet it's half of the revolution
 unsigned int rpm; //the rotation speed of the motor
 unsigned long timeold; //the start time of every 20 motor rotation  
 unsigned int num; // the number of rounds the motor has rotate

void stopIfFault()
{
  if (md.getM1Fault())
  {
    md.disableDrivers();
    delay(1);
    Serial.println("M1 fault");
    while (1);
  }
  if (md.getM2Fault())
  {
    md.disableDrivers();
    delay(1);
    Serial.println("M2 fault");
    while (1);
  }
}

  void setup()
{
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP); //put an pull up resister at the input pin

  //initialize variables
  half_revolutions = 0; 
  rpm = 0;
  timeold = 0;
  num = 0;

  //print out the start line
  while (! Serial);
  Serial.println("\n\n\nDual G2 High Power Motor Shield");


  the following should be uncomment to make the motor work:
  /* 
  md.init();
  md.calibrateCurrentOffsets();
  */

  //using interrupt function to get every signal from the sensor
  attachInterrupt(0, magnet_detect, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)
 
  delay(10);

}


void loop()
{
  //every 10 rounds (the motor moves) we will calculate the speed of the motor
  // and start the next round of movement
   if (half_revolutions >= 20) { 
     rpm = 30*1000/(millis() - timeold)*half_revolutions; // calculate the speed of the motor
     timeold = millis(); //assign the current time to the start time of the new round
     half_revolutions = 0;
     delay(500);
     Serial.print("Speed: ");
     Serial.print(rpm,DEC);
     Serial.println(" r/min");

     // just a test, for every 20 times a magenet pass the sensor, 
     // we call the runMotor function to make the motor rotate a little bit
     // currently it's just printing statements since I don't have the motor 
     runMotor();
   
     
   }
}



 void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
 {
   half_revolutions++;

   // every 2 half revolution we increase the number of rounds 
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

 void runMotor()
 {
   while (! Serial);
   Serial.println("motor runs!");
 
  the following should be uncomment to make the motor work:
 /*
  md.enableDrivers();
  delay(1);  // The drivers require a maximum of 1ms to elapse when brought out of sleep mode
  int i = 200;
    md.setM2Speed(i);
    stopIfFault();
    if (i%200 == 100)
    {​​​​​​​
      Serial.print("M2 current: ");
      Serial.println(md.getM2CurrentMilliamps());
    }​​​​​​​
    delay(2);


  md.disableDrivers(); // Put the MOSFET drivers into sleep mode.
  delay(100);
  */
 
 }
