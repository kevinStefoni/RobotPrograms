#!/usr/bin/env python
#!/usr/bin/python3
from __future__ import print_function
from __future__ import division

import serial
import time     # import the time library for the sleep function
import brickpi3 # import the BrickPi3 drivers

BP = brickpi3.BrickPi3()
# BP.set_sensor_type(BP.PORT_2, BP.SENSOR_TYPE.EV3_COLOR_COLOR)
# color = ["none", "Black", "Blue", "Green", "Yellow", "Red", "White", "Brown"]

# Start the serial communication for the PI. The baud rate is hard coded on the PRIZM, because
# you cannot use serial communication to send a baud rate that is then used to establish serial communication.
def initSerComm(baudrate: int):
    try:
        BP = brickpi3.BrickPi3() # Create an instance of the BrickPi3 class. BP will be the BrickPi3 object.
        print("BrickPi3 connected and running.")
    except brickpi3.FirmwareVersionError as error:
        print(error)
    except:
        print("Communication with BrickPi3 unsuccessful.")

    print("Pi: set up serial port; this will *** RESET *** PRIZM board !!!!")
    global ser
    ser = serial.Serial('/dev/ttyUSB0', baudrate, timeout=1)

def handShake():
    while True:
        send("hsk")
        input = ser.read()
        print(input.decode("utf-8"))
        if input.decode("utf-8") != "":
            break
            

# Ask PRIZM to move robot forward at <power> speed
def moveForward(power: int):
    cmd = "fow " + str(power)
    send(cmd)

# Ask PRIZM to move robot backward at <power> speed
def moveBackward(power: int):
    cmd = "bak " + str(power)
    send(cmd)

# Ask PRIZM to end
def endPrizm():
    cmd = "end"
    send(cmd)

# Receive the sonic sensor reading and return it
def getSonicSensorCM():
    while True:
        send("rss")
        input = ser.readline()
        if input.decode("utf-8") != "":
            break
    return int(input)

# Turn the robot left
def turnLeft(power: int):
    cmd = "lft " + str(power)
    send(cmd)

# Turn the robot right
def turnRight(power: int):
    cmd = "rit " + str(power)
    send(cmd)

# set the power of just the left motor
def setLeftMotor(power :int):
    cmd = "slm " + str(power)
    send(cmd)

# set the power of just the right motor
def setRightMotor(power: int):
    cmd = "srm " + str(power)
    send(cmd)

# perform a running left turn
def runningLeftTurn(power: int, extra: int):
    setLeftMotor(power + extra)
    setRightMotor(power)

# perform a running right turn
def runningRightTurn(power: int, extra: int):
    setLeftMotor(power)
    setRightMotor(power + extra)

# perform a running right turn
def runningBackLeftTurn(power: int, extra: int):
    setLeftMotor(-1 * (power + extra))
    setRightMotor(-1 * power)

# perform a running right turn
def runningBackRightTurn(power: int, extra: int):
    setLeftMotor(-1 * power)
    setRightMotor(-1 * (power + extra))

# Sends the cmd and flushes the buffer automatically
def send(cmd: str):
    ser.write(str(cmd).encode() + "\n".encode())
    ser.flush()
