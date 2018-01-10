# SmartShoe

Get good grades with SmartShoe!!!

# What is SmartShoe?

SmartShoe is a project aimed at providing an easy way of communicating without being noticed. The idea is to implement a sender and various receivers that can be hidden in our clothing (i.e. shoes). The sender and receivers may transmit valuable information without suspicious action.

# How is it made?

The prototype consists of two kinds of shoes: SmartShoe-sender and SmartShoe-receiver. SmartShoe-sender utilized MSP432 LaunchPad as its brain, with the LaunchPad's BLE add-on and a force sensor for sender to input data. SmartShoe-receiver is implemented using raspberry pi 3, with a vibrating sensor to transmit the received data to the user.
 
![alt text]( https://github.com/NTUEE-ESLab/2017Fall-SmartShoe/blob/gh-pages/Images/sender_bb.jpg?raw=true "SmartShoe-sender")
![alt text]( https://github.com/NTUEE-ESLab/2017Fall-SmartShoe/blob/gh-pages/Images/receiver_bb.jpg?raw=true  "SmartShoe-receiver")

# Usages

## SmartShoe-sender

To use SmartShoe-sender, the sender must send data through pressing the force sensor. SmartShoe-sender provides four different alphabets to send by default(A,B,C,D). Each alphabet would correspond to a specific pattern of pressing the force sensor. Instead of having the user to learn data encoding protocols, SmartShoe lets the sender to customize how each input should be like. 

To use SmartShoe-sender to costumize your input pattern and send data, please follow the steps below

1. Power on SmartShoe-sender. Once the shoe is powered, it automatically enters initialization mode. Any configuration you made will be lost when the shoe loses power.
	
2. In the initializtion mode, press push-button2. A green LED will light up, when this happens, press the force sensor with the pattern you wish to represent the alphabet 'A'. SmartShoe stores up to 3 seconds of pressing pattern, if your pressing pattern exceeds three seconds, the pattern of the middle three seconds would be selected as the specific pattern. It is advised that your pressing pattern is within three seconds.
	
3. Wait for the green LED to go off. SmartShoe-sender has now initialized what kind of pressing pattern represents 'A'. 
	
4. Repeat step 2 and step 3 three more times to specify the patterns for 'B', 'C', and 'D'.
	
5. Now all patterns have been specified, all the subsequent presses you made will be decoded using the data your have input in the initialization mode and sent to SmartShoe-receiver.

SmartShoe-sender uses vector manipulation to determine what your input should be, to minimize error

1. Be sure your input pressing pattern matches the pattern in initialization mode, especially in frequency.
	
2. Make sure to wait at least one second between each pressing pattern.(It is recommended to wain up to three seconds if time permits.)

## SmartShoe-receiver

To use SmartShoe-receiver, perform the following steps

1. Make sure a SmartShoe-sender is working nearby.
	
2. Power on your SmartShoe-receiver.
	
3. The vibration motor is configured to vibrate each alphabet to you with the following pattern(each on/off takes 0.3 second)
	
##### Vibration Pattern:

|Alphabets   |'A'         |'B'         |'C'         |'D'         |
|:----------:|:----------:|:----------:|:----------:|:----------:|
|Pattern     |on/off	  |on/off x2   |on/off x3   |on/off x4   |



# I want my own SmartShoe

The following information will give you enough knowledge about how to build your own SmartShoe prototype.

## Building your own SmartShoe-sender:

Hardware requirements:
	MSP432P401R LaunchPad
	CC2650 Module BoosterPack
	Force Sensor x 1
	5.6k ohm resistor(5%) x1

To configure the software environment to build SmartShoe-sender source code, you need to first install Energia. After installation, have 'Energia MSP432 boards' installed(Tools -> Boards -> Boards Manager). Make sure to install 'Energia MSP432 boards' and don't install 'Energia MSP432 EMT RED boards'. Once the board is correctly installed, go to 'Sketch -> Include Library -> Library Manager' and install BLE.

Finally, you need to build and configure CMSIS-DSP library on Energia, please refer to [Energia-CMSIS Library](https://github.com/b03901060/CMSIS-DSP-Library-for-MSP432-on-Energia-IDE) for help.

## Building SmartShoe-receiver

Hardware requirements:
	Raspberry Pi 3
	RVN 1305 Vibrate Motor
	
Step 1. Put `read_ans.py` to appropriate path.

Step 2. Set the start-up program on RPi 3

   open `~/.config/lxsession/LXDE-pi/autostart` and choose the text editor.

   scroll to the bottom and add a line

   `@/usr/bin/python path_to_python_file`

   You should replace `path_to_python_file` to your on path links to `read_ans.py`

Step 3. Reboot RPi 3. (Execute the command `sudo reboot`)

Step 4. You can see the program `read_ans.py` is running at the background.

## Using Powerbank
We cannot use the power from PC when we use it for application. Therefore, using Powerbank to replace the power from PC or 110V power. By our experiment, the circuit can work normally.

# Experiment Result
## SmartShoe-sender
![alt text](https://github.com/NTUEE-ESLab/2017Fall-SmartShoe/blob/gh-pages/Images/Demo_MSP432.jpg?raw=true "SmartShoe-sender")

## SmartShoe-receiver
![alt text](https://github.com/NTUEE-ESLab/2017Fall-SmartShoe/blob/gh-pages/Images/Demo_RPi.jpg?raw=true "SmartShoe-receiver")

## Demo Vedio
1. [Demo-1 User Defined Pattern](https://youtu.be/x6R_morT4zs)

2. [Demo-2 Test Transmission](https://youtu.be/oovrMNNiGNI)

(Note: We use LED to show the result due to the fact that the vibration is small.)


# Future Goal
1. Using more complicated transmission protocol to pass the alphabet A~Z

2. Embedded the circuit and the power into shoes.

3. Although the accuracy is high enough, we want to achieve 100% accuracy.


# Reference
1. [FSR-402 Datasheet](http://www.trossenrobotics.com/productdocs/2010-10-26-DataSheet-FSR402-Layout2.pdf)

2. [Start-up Program on RPi 3](http://icodding.blogspot.tw/2016/01/raspberry-pi-linux-pi-sell-script.html)

3. [Gatttool Usage](http://www.humbug.in/2014/using-gatttool-manualnon-interactive-mode-read-ble-devices/)

4. [Energia-BLE](http://energia.nu/reference/ble/)

5. [Energia-MSP432](http://energia.nu/pin-maps/guide_msp432p401r/)

6. [Energia-CMSIS Library](https://github.com/b03901060/CMSIS-DSP-Library-for-MSP432-on-Energia-IDE)
