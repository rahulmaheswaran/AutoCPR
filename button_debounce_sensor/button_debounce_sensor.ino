#include "DualG2HighPowerMotorShield.h"
#include <avr/wdt.h>

 

// Uncomment the version corresponding with the version of your shield.
//DualG2HighPowerMotorShield24v14 md;
// DualG2HighPowerMotorShield18v18 md;
 DualG2HighPowerMotorShield24v18 md;
// DualG2HighPowerMotorShield18v22 md;


const byte interruptPinON = 3;
const byte interruptPinOFF = 21;
const int hallPin = 2;
volatile byte state = LOW;
 

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
  pinMode(interruptPinON, INPUT_PULLUP);
  pinMode(interruptPinOFF, INPUT_PULLUP);
  pinMode(hallPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPinON), turnON, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPinOFF), turnOFF, CHANGE);
  Serial.begin(115200);
  Serial.println("Dual G2 High Power Motor Shield");
  md.init();
  md.calibrateCurrentOffsets();

 

  delay(10);

 

  // Uncomment to flip a motor's direction:
  //md.flipM1(true);
  //md.flipM2(true);
}

 

void loop()
{
  md.enableDrivers();
  delay(1);  // The drivers require a maximum of 1ms to elapse when brought out of sleep mode
    
}

void turnON() {
 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (interrupt_time - last_interrupt_time > 200)
 {
   Serial.println("Turning On");
   runMotor();
 }
 last_interrupt_time = interrupt_time;
}

void turnOFF() {
 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (interrupt_time - last_interrupt_time > 200)
 {
   Serial.println("Turning OFF");
 offMotor();
 }
 last_interrupt_time = interrupt_time;
}

void runMotor(){

  

for (int i = 0; i < 300; i++){
  md.setM2Speed(i);
    stopIfFault();
    if (i%200 == 100)
    {
      Serial.print("M2 current: ");
      Serial.println(md.getM2CurrentMilliamps());
    }
   }
}

void offMotor(){

for (int i = 300; i > 0; i--){
  md.setM2Speed(i);
    stopIfFault();
    if (i%200 == 100)
    {
      Serial.print("M2 current: ");
      Serial.println(md.getM2CurrentMilliamps());
    }
   }
   delay(5);
}

void hall_ISR() 
{
   Serial.print("Hall Sensor");
  //runMotor();
}
