# -*- coding: utf-8 -*-
"""
Created on Fri Feb 26 10:00:52 2016

@author: PapyChaudière
"""

# Import package
import socket
import time
import RPi.GPIO as io
io.setmode(io.BCM)
io.setwarnings(False)

# Global variable
eventLeftCounter = 0
eventRightCounter = 0

# Define GPIO with BCM io
LEFT_PWM = 18
RIGHT_PWM = 19

# Set up RPi.GPIO Pi
io.setup(LEFT_PWM, io.OUT)
pwm_left = io.PWM(LEFT_PWM, 4000)
pwm_left.ChangeFrequency(20000)
pwm_left.start(50)

io.setup(RIGHT_PWM, io.OUT)
pwm_right = io.PWM(RIGHT_PWM, 4000)
pwm_right.ChangeFrequency(20000)
pwm_right.start(50)

# Set the socket with server
s = socket.socket
host = '10.42.0.1'# ip of bugro's PC
port = 1200

try:
    s.connect((host,port))

except:
    print("Unable to connect to server.\nCheck if IP address is correct and your firewall")

# Main Program

try:
        print(str(s.recv(1024)))

        while True:

            data = str(s.recv(1024))
            if(data[0] == "R"):

                dataSplited = data.split("=")
                dataR = dataSplited[1].split("L")[0]
                dataL = dataSplited[2]
                print dataR
                print dataL
                dataR = int(dataR)
                dataL = int(dataL)
                pwm_right.ChangeDutyCycle(float(dataR))
                pwm_left.ChangeDutyCycle(float(dataL))

            else:
                print "Command was lost"
except:

        pwm_left.stop()         # stop the white PWM output
        pwm_right.stop()        # stop the red PWM output
        io.cleanup()            # clean up GPIO on CTRL+C exit
        print("\nEnd of Program\n")
        print("\nYou've been disconnected")
        s.close()




