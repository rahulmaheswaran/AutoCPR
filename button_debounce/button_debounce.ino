#include "DualG2HighPowerMotorShield.h"

 

// Uncomment the version corresponding with the version of your shield.
//DualG2HighPowerMotorShield24v14 md;
// DualG2HighPowerMotorShield18v18 md;
 DualG2HighPowerMotorShield24v18 md;
// DualG2HighPowerMotorShield18v22 md;


const byte interruptPin = 3;
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
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, HIGH);
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
  int i = 100;
    md.setM2Speed(i);
    stopIfFault();
    if (i%200 == 100)
    {
      Serial.print("M2 current: ");
      Serial.println(md.getM2CurrentMilliamps());
    }
    delay(2);

 

  md.disableDrivers(); // Put the MOSFET drivers into sleep mode.
  delay(100);
}

void blink() {
 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (interrupt_time - last_interrupt_time > 200)
 {
    Serial.print("Works!");
 }
 last_interrupt_time = interrupt_time;
}
