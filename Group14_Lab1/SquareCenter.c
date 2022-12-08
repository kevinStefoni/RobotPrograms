/*  PRIZM Controller example program
 *  Spin DC motor channel 1 for 5 seconds, then coast to a stop.
 *  After stopping, wait for 2 seconds, spin in opposite direction.
 *  Continue to repeat until RED reset button is pressed.
 *  author PWU on 08/05/2016
*/
  #include <Wire.h>
  #include <PRIZM.h>    // include the PRIZM library in the sketch
  PRIZM prizm;  // instantiate a PRIZM object “prizm” so we can use its functions
    

void setup() {  

  prizm.PrizmBegin();   // Initialize the PRIZM controller
  Serial.begin(9600);
}

void loop() {     // repeat in a loop
  int i = 1;
  
  // measure first part of length
  int l1 = prizm.readSonicSensorCM(3);
  Serial.print(prizm.readSonicSensorCM(3));   // print the CM distance to the serial monitor
  Serial.println(" Centimeters for L1");
  
  // turn 180 degrees
  prizm.setMotorPower(1,25);
  delay(4250);
  prizm.setMotorPower(1,0);
  delay(2000);
  
  
  // measure second part of length
  int l2 = prizm.readSonicSensorCM(3);
  Serial.print(prizm.readSonicSensorCM(3));   // print the CM distance to the serial monitor
  Serial.println(" Centimeters for L2");
  delay(3000);
  
  // calculate distance needed from wall to be in center for this dimension
  int lengthCenterDistance = (l1 + l2) /2;
  Serial.print("center is ");
  Serial.println(lengthCenterDistance);
  
  // 15.24 cm is half of robot size
  while(fabs(prizm.readSonicSensorCM(3) - lengthCenterDistance) >= 2){
    Serial.print("move loop #");
    Serial.print(i);
    Serial.print(": ");
    i++;
    
    if(prizm.readSonicSensorCM(3) < lengthCenterDistance)
    {
       // move backwards
       prizm.setMotorPower(1, 25); 
       prizm.setMotorPower(2, -25);  
    }
    else if(prizm.readSonicSensorCM(3) > lengthCenterDistance)
    {
      // move forwards
      prizm.setMotorPower(1,-25); 
      prizm.setMotorPower(2, 25);
    }
    Serial.print(prizm.readSonicSensorCM(3));
    Serial.println("CM is the current distance");
  }
  
  prizm.setMotorPower(1, 125);
  prizm.setMotorPower(2, 125);
  Serial.print(prizm.readSonicSensorCM(3));
  Serial.println("CM is the current distance");
  Serial.println("Woohoo time to stop");
  
  // turn 180 degrees
  prizm.setMotorPower(1,25);
  delay(2125);
  prizm.setMotorPower(1,0);
  delay(2000);
  
    while(fabs(prizm.readSonicSensorCM(3) - lengthCenterDistance) >= 2){
    Serial.print("move loop #");
    Serial.print(i);
    Serial.print(": ");
    i++;
    
    if(prizm.readSonicSensorCM(3) < lengthCenterDistance)
    {
       // move backwards
       prizm.setMotorPower(1, 25); 
       prizm.setMotorPower(2, -25);  
    }
    else if(prizm.readSonicSensorCM(3) > lengthCenterDistance)
    {
      // move forwards
      prizm.setMotorPower(1,-25); 
      prizm.setMotorPower(2, 25);
    }
    Serial.print(prizm.readSonicSensorCM(3));
    Serial.println("CM is the current distance");
  }
  
  prizm.setMotorPower(1, 125);
  prizm.setMotorPower(2, 125);
  Serial.print(prizm.readSonicSensorCM(3));
  Serial.println("CM is the current distance");
  Serial.println("Woohoo time to stop");
  
  prizm.PrizmEnd();
              
  
}






