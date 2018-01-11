import RPi.GPIO as GPIO
from subprocess import call


GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.IN)

from time import sleep
sleep(10)

count = [1,1,1,1,1,1,1,1]

while (True):
    a = GPIO.input(4)
    count.append(a)
    count.pop(0)
    sleep(0.1)
    #print(sum(count))
    if sum(count) == 0:
        #print(sum(count))
        call("sudo shutdown -h now",shell = True)
        #print("HAHAHA")
