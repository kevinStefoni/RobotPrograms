#!/usr/bin/env python
#!/usr/bin/python3
from __future__ import print_function
from __future__ import division

import serial
import time

import time     # import the time library for the sleep function
import brickpi3 # import the BrickPi3 drivers

BP = brickpi3.BrickPi3()
BP.set_sensor_type(BP.PORT_2, BP.SENSOR_TYPE.EV3_COLOR_COLOR)
color = ["none", "Black", "Blue", "Green", "Yellow", "Red", "White", "Brown"]

try:
    BP = brickpi3.BrickPi3() # Create an instance of the BrickPi3 class. BP will be the BrickPi3 object.
    print("BrickPi3 connected and running")
except brickpi3.FirmwareVersionError as error:
    print(error)
except:
    print("Communication with BrickPi3 unsuccessful")

# test communication with Tetrix controller
print("Pi: set up serial port; this will *** RESET *** PRIZM board !!!!")
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
# Dakai: init serial port will re-set PRIZM board !!!!
# Dakai: need to start python code on Pi first,
#       and then press GREEN button on PRIZM !!!!
time.sleep(2) # wait for 1 second for reset PRIZM

print ("***************************************************** ")
print("Please press the GREEN button to start PRIZM board !!!!")
print ("***************************************************** ")


#send out command
cmd = 4
while 1:
        sColor = BP.get_sensor(BP.PORT_2);
        print("Color: " + color[sColor] + " Command: " + str(cmd));
        ser.write(str(cmd).encode())
        ser.flush()

        # green
        if BP.get_sensor(BP.PORT_2) == 3:
            cmd = 5
                
        # red
        elif BP.get_sensor(BP.PORT_2) == 5:
            cmd = 6 

        # white 
        elif BP.get_sensor(BP.PORT_2) == 6:
            cmd = 7             
    
        # not white 
        else:
            cmd = 8




        time.sleep(0.1)
