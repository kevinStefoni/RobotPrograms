from mySerCommLibrary import *
import time
import random

color = ["none", "Black", "Blue", "Green", "Yellow", "Red", "White", "Brown"]
progress = ['none']

initSerComm(9600)
handShake()
time.sleep(1)

count = 0
speed = 10
bonus = 10
degreeFactor = 2.5
alternator = 1
breaker = False
initialTime = time.time()
while True:
    while (time.time() - initialTime) < 1.5:

        if getSonicSensorCM() < 45 and alternator == 0:
            runningRightTurn(speed, bonus * 4)
        elif getSonicSensorCM() < 45 and alternator == 1:
            runningLeftTurn(speed, bonus * 4)

        if getSonicSensorCM() < 15:
            moveBackward(speed)
            time.sleep(0.75)

        while color[getColor()] == "Yellow" or color[getColor()] == "Brown":
            print("HOW MANY YELLOW TAPES? prog: " + str(progress))
            if CheckList(progress, "Inner") is False:
                progress.append("Inner")
                inititalTime = time.time()
                time.sleep(1.75) 
                break
            else:
                moveBackward(speed)
                time.sleep(0.5)
                turnLeft(speed)
                time.sleep(random.uniform(3, 5))
                moveForward(speed)

        while color[getColor()] == "White" or color[getColor()] == "Blue":
            print("HOW MANY WHITE TAPES? prog: " + str(progress))
            if CheckList(progress, "Inner") is True:
                stop()
                endPrizm()
            if CheckList(progress, "Middle") is True:
                progress.remove("Middle")
            if CheckList(progress, "Outer") is False:
                progress.append("Outer")                
                inititalTime = time.time()
                time.sleep(1.75)                 
                break
            else:
                moveBackward(speed)
                time.sleep(0.5)
                turnLeft(speed)
                time.sleep(random.uniform(3, 8))
                moveForward(speed)
        
        while color[getColor()] == "Red":
            print("HOW MANY RED TAPES? prog: " + str(progress))
            if CheckList(progress, "Inner") is True:
                progress.remove("Inner")
            if CheckList(progress, "Middle") is False:
                progress.append("Middle")
                inititalTime = time.time()
                time.sleep(1.75) 
            else:
                moveBackward(speed)
                time.sleep(0.5)
                turnLeft(speed)
                time.sleep(random.uniform(3, 5))
                moveForward(speed)

        
        # if color[getColor()] == "Blue":
        #     print("BLUE!! prog: " + str(progress))
        #     if CheckList(progress, "Inner") is True:
        #         stop()
        #         endPrizm()

    initialTime = time.time()
    alternator = (alternator + 1) % 2
    if(alternator == 0):
        runningLeftTurn(speed, bonus)
    else:
        runningRightTurn(speed, bonus)
