import os
import time
import RPi.GPIO as GPIO
import requests

GPIO.setmode(GPIO.BCM)
GPIO.setup(26,GPIO.OUT)

ans_num = 0

ans_queue = []

t1 = time.time()
while True:
    text = os.popen("sudo gatttool -b A0:E6:F8:BA:20:04 --char-read -a 0x0022").read()
    #print(texT)
    text = text.strip("\n").split(" ")
    if len(text) != 5:
        #print("len != 5")
        continue
    if text[-2].isdigit() and text[-3].isdigit():
        i = int(text[-3])
        if ans_num != i:
            ans_num = i
            num = int(text[-2])
            print(num)
            for a in range(num):
                GPIO.output(26,GPIO.HIGH)
                time.sleep(0.5)
                GPIO.output(26,GPIO.LOW)
                time.sleep(0.5)
            ans_queue.append(num)
            print(ans_queue)

    temp = time.time()
    if temp - t1 > 20.0 and len(ans_queue) > 0:
        str_name = "https://api.thingspeak.com/update?api_key=QIU4JO5XYN5I1583&field1="
        str_name += str(ans_queue[0])
        try:
            r = requests.get(str_name)
            ans_queue.pop(0)
            print("Successful!!!")
        except:
            print("Error")
        t1 = temp
        print(ans_queue)
