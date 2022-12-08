#include <Wire.h>

/*   PRIZM Controller example program
 *   This example program will read the digital signal of the
 *   Ultrasonic sensor attached to the digital sensor port D3.
 *   The distance in centimeters of an object placed in front
 *   of the sensor will be sent to the serial monitor window.
 */

  #include <PRIZM.h>      // include the PRIZM Library
  PRIZM prizm;            // instantiate a PRIZM object “prizm” so we can use its functions

void setup() {     //this code runs once

  prizm.PrizmBegin();     // initialize PRIZM

  Serial.begin(9600);     // configure the serial monitor for 9600 baud rate
 
}

void loop() {     //this code repeats in a loop

  Serial.print(prizm.readSonicSensorCM(3));   // print the CM distance to the serial monitor

  Serial.println(" Centimeters");             // print " Centimeters"

  //delay(200);   //slow down loop. Wait for 200ms to keep from printing to serial monitor to fast.
  if(prizm.readSonicSensorCM(3) < 10)
  {
    prizm.setMotorPower(1,25);
    prizm.setMotorPower(2,-25);
  }
  else if(prizm.readSonicSensorCM(3) > 20)
  {
    prizm.setMotorPower(1,-25);
    prizm.setMotorPower(2,25);
  }
  else
  {
    prizm.setMotorPower(1,0);
    prizm.setMotorPower(2,0);
  }
}