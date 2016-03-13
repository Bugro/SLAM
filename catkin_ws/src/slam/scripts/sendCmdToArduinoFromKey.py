#!/usr/bin/env python

import time
import serial

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=9600
)

ser.isOpen()

print 'Enter your commands below.\r\nInsert "exit" to leave the application.'

input = 1
while 1 :
    # get keyboard input
    input = raw_input("input >> ")

    if input == 'exit':
        ser.close()
        exit()
    else:
        # send the commands to the robot

        right = 0;
        left = 0;
	
        if input == 'z':
            right = 180
            left = 177
        elif input == 'd':
            right = 82
            left = 167
        elif input == 'q':
            right = 172
            left = 88
        else:
            right = 128
            left = 128

        ser.write(chr(12))
        ser.write(chr(13))
        ser.write(chr(right))
        ser.write(chr(left))
        #ser.write(chr(12))
        #ser.write(chr(13))
        #ser.write(chr(right))
        #ser.write(chr(left))

