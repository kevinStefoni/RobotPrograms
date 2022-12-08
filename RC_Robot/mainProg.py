from mySerCommLibrary import *
import time
import curses

initSerComm(9600)
handShake()
time.sleep(1)

speed = 15

shell = curses.initscr()
shell.nodelay(True)

try:
    curses.cbreak()
    while True:
        if getSonicSensorCM() < 15:
            moveForward(0)

        key = shell.getch()
        if key == 119:
            print("move forward")
            moveForward(speed)
        elif key == 115:
            print("move backward")
            moveBackward(speed)
        elif key == 97:
            print("forward left turn")
            runningLeftTurn(speed, 12)
        elif key == 100:
            print("forward right turn")
            runningRightTurn(speed, 12)
        elif key == 113:
            print("left turn")
            turnLeft(speed)
        elif key == 101:
            print("right turn")
            turnRight(speed)
        elif key == 102:
            print("read sonic sensor")
            getSonicSensorCM()
        elif key == 32:
            print("speed boost!")
            moveForward(speed + 10)
        elif key == 114:
            print("stop")
            moveForward(0)
        elif key == 122:
            print("backward left turn")
            runningBackLeftTurn(speed, 12)
        elif key == 99:
            print("backward left turn")
            runningBackRightTurn(speed, 12)
        

except KeyboardInterrupt:
    curses.nocbreak()
    curses.endwin()