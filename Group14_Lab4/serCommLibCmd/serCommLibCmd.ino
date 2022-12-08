#include <Wire.h>    // include the PRIZM library in the sketch
#include <PRIZM.h>    // include the PRIZM library in the sketch
PRIZM prizm;          // instantiate a PRIZM object “prizm” so we can use its functions

String inputString = "";
String outputString = "";

boolean stringComplete = false;
int inputIndex = 0;

String strs[3];
int StringCount = 0;

int numParameters = 0;

void setup()
{
  // begin the serial communication
  prizm.PrizmBegin();
  Serial.begin(9600);
  
  // reserve appropriate number of bytes
  inputString.reserve(200);
  outputString.reserve(200);
  
}

void loop()
{

  serialEvent(); // inputString should now have the full command and stringComplete is now true
  
  if(stringComplete)
  {
     inputString.trim(); // remove outer whitespace
     parseCommand(); // parse commands into cmdString, paraOne, and paraTwo
    
    if(strs[0] == "hsk")
    {
       Serial.write('A'); 
    }
    // Move forward at <paraOne> power
    else if(strs[0] == "fow")
    {
       prizm.setMotorPower(1, -1 * strs[1].toInt());
       prizm.setMotorPower(2, strs[1].toInt());  
    }
    // Move backward at <paraTwo> power
    else if(strs[0] == "bak")
    {
       prizm.setMotorPower(1, strs[1].toInt());
       prizm.setMotorPower(2, -1 * strs[1].toInt());   
    }
    // End the prizm run == pressing red button
    else if(strs[0] == "end")
    {          
      // end the prizm
      prizm.PrizmEnd(); 
    }
    // Receive request to send reading from sonic sensor
    else if(strs[0] == "rss")
    {
      Serial.println(String(prizm.readSonicSensorCM(3)));      
    }
    else if(strs[0] == "lft")
    {
      prizm.setMotorPower(1, strs[1].toInt());
      prizm.setMotorPower(2, strs[1].toInt());
    }
    else if(strs[0] == "rit")
    {
     prizm.setMotorPower(1, -1 * strs[1].toInt());
     prizm.setMotorPower(2, -1 * strs[1].toInt());
    }
    inputString = "";
    stringComplete = false;
    StringCount = 0;
  }

     
  
}

/*
 This formulates the input string from the buffer and sets stringComplete to true.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


void parseCommand()
{
  
  while (inputString.length() > 0)
  {
    int index = inputString.indexOf(' ');
    if (index == -1) // No space found
    {
      strs[StringCount++] = inputString;
      break;
    }
    else
    {
      strs[StringCount++] = inputString.substring(0, index);
      inputString = inputString.substring(index+1);
    }
  }
  
  
}
