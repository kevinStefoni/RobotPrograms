/*
  Serial Call and Response
 Language: Wiring/Arduino

 This program sends an ASCII A (byte of value 65) on startup
 and repeats that until it gets some data in.
 Then it waits for a byte in the serial port, and
 sends three sensor values whenever it gets a byte in.

 Thanks to Greg Shakar and Scott Fitzgerald for the improvements

   The circuit:
 * potentiometers attached to analog inputs 0 and 1
 * pushbutton attached to digital I/O 2

 Created 26 Sept. 2005
 by Tom Igoe
 modified 24 April 2012
 by Tom Igoe and Scott Fitzgerald

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialCallResponse

 */
 
#include <Wire.h>    // include the PRIZM library in the sketch
#include <PRIZM.h>    // include the PRIZM library in the sketch
PRIZM prizm;          // instantiate a PRIZM object “prizm” so we can use its functions

int firstSensor = 0;    // first analog sensor
int inByte = 0;         // incoming serial byte
int prevByte = 0;
int endGreen = 0;

int count = 0; 

void setup()
{
  prizm.PrizmBegin();
  // start serial port at 9600 bps:
  Serial.begin(9600, SERIAL_8N1);
}

void loop()
{
  // read in ** one byte **, and control motor based on the reading
  if (Serial.available() > 0) {
    // get incoming single byte:
    delay(10);
    prevByte = inByte;
    inByte = Serial.read();
    
    if(prevByte == inByte)
      count ++;
    else
      count = 1;
      
    if(prevByte == '5' && inByte != '5')
      endGreen = 1;
    
     
     switch (inByte){
       case '4':{
         break;
       }
       case '5':{
         
         // green -- stop
         if(endGreen == 1)
         {
           prizm.setMotorPower(1, 125);
           prizm.setMotorPower(2, 125);
           prizm.PrizmEnd();
         }
         else
         {
           prizm.setMotorPower(1, -25);
           prizm.setMotorPower(2, 25);
         }
         break;
       }
       case '6':{
         
         prizm.setMotorPower(1, 25);
         prizm.setMotorPower(2, 25);
         
         // red -- turn
         while(1)
         {
             if (Serial.available() > 0) {
               inByte = Serial.read();
             }
             
           if(inByte == '7')
             break;
         }
         break;
       } 
       case '8':{
         
         // not white -- course correction
         if(count < 10)
         {
         prizm.setMotorPower(1, -15);
         prizm.setMotorPower(2, -15);
         }
         else
         {
           // count = 1
          prizm.setMotorPower(1, 15);
          prizm.setMotorPower(2, 15);
         }
         
         break;
       }
       case '7':{
        
         // white
         if(count == 1)
           delay(20);
         prizm.setMotorPower(1, -10);
         prizm.setMotorPower(2, 10);
         break;
         
       }
       default: break; 
     }  
      

  }
}
