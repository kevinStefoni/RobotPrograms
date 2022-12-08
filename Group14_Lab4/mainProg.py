from mySerCommLibrary import *
import time
import random

initSerComm(9600)
handShake()
time.sleep(1)

random.seed(time.time());
initialTime = time.time()

list = [0, 1]

while (time.time() - initialTime) < 120:
    while(getSonicSensorCM() > 40):
        moveForward(10)
    while(getSonicSensorCM() < 50):
        moveBackward(10)

    if(random.choice(list) == 0):
        turnLeft(10)
    else:
        turnRight(10)
    time.sleep(random.random() * 5)    

endPrizm()
