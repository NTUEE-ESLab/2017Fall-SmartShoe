import os
import time
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(26,GPIO.OUT)

ans_num = 0

while True:
    text = os.popen("sudo gatttool -b A0:E6:F8:BA:20:04 --char-read -a 0x0022").read()
    print(text)
    text = text.strip("\n").split(" ")
    if text[-2].isdigit() and text[-3].isdigit():
        i = int(text[-3])
        if ans_num != i:
            ans_num = i
            num = int(text[-2])
            for a in range(num):
                GPIO.output(26,GPIO.HIGH)
                time.sleep(0.3)
                GPIO.output(26,GPIO.LOW)
                time.sleep(0.3)


