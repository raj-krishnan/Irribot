Pending: YouTube link to the ScreenCast and/or project video. 

2014-CS101

Group Number:331

Team:
Mahen Kinnur	140040024
Shivank Kumar	140010024
Raj Krishnan	140010007
Jagesh Golwala	14D070005

Title: Irribot

Firebird V Setup:
1.	2 servo motors with a small arm for each should be attached to slot 1 and 2.
2.	Moisture sensor should be mounted on arm of servo 1
3.	Analog output of moisture sensor should be connected to ADC14
4.	Container for water should be mounted at a height
5.	A pipe from the container should be mounted on the arm of servo 2 

Spftware Setup:

1.	Open Atmel Studio and create a new project
2.	Delete the existing code and replace it with the code provided in Irribot.c
3.	Add the files lcd.h, servo.h, moistureSensor.h, motion.h and shaftcount.h to the folder in the root
	of the directory made for the project
4.	Build the solution by clicking the respective button or press F7
5.	Open AVR Bootloader and select ATmega2560 as your microcontroller
6.	Connect the Firebird V robot (in bootloader mode) to the computer and wait for it to be detected.
7.	It should automatically select the COM port
8.	Set the BAUD rate to 115200
9.	Insert the link to the .hex file made on compiling the project in Atmel Studio
10.	Press program and wait for the code to be burnt to the device
11.	Press reset and enjoy experimenting with Irribot


Project Demo: https://youtu.be/pjOwyY-QRgs
Software Setup: https://youtu.be/bzmgr9DaA2M
