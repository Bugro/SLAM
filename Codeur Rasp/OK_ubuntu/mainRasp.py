# -*- coding: utf-8 -*-
"""
Created on Fri Feb 26 10:00:52 2016

@author: PapyChaudière
"""

# Import package
import socket
import threading
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

LEFT_IT = 17
LEFT_A = 27
LEFT_B = 22

RIGHT_IT = 16
RIGHT_A = 20
RIGHT_B = 21

# Set up RPi.GPIO Pi
io.setup(LEFT_PWM, io.OUT)
pwm_left = io.PWM(LEFT_PWM, 4000)
pwm_left.ChangeFrequency(20000)
pwm_left.start(50)

io.setup(RIGHT_PWM, io.OUT)
pwm_right = io.PWM(RIGHT_PWM, 4000)
pwm_right.ChangeFrequency(20000)
pwm_right.start(50)

io.setup(LEFT_IT, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(RIGHT_IT, io.IN, pull_up_down=io.PUD_DOWN)

io.setup(LEFT_A, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(LEFT_B, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(RIGHT_A, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(RIGHT_B, io.IN, pull_up_down=io.PUD_DOWN)

# Interrupt timer init
class MyTimer:

    def __init__(self, tempo, target, args= [], kwargs={}):
        self._target = target
        self._args = args
 	self._kwargs = kwargs
        self._tempo = tempo

    def _run(self):
        self._timer = threading.Timer(self._tempo, self._run)
        self._timer.start()
        self._target(*self._args, **self._kwargs)

    def start(self):
        self._timer = threading.Timer(self._tempo, self._run)
        self._timer.start()

    def stop(self):
        self._timer.cancel()

# Interrupt timer function
def timer_handler():

	global eventLeftCounter
	global eventRightCounter

	s.sendall(str(eventLeftCounter))
	s.sendall(str(eventRightCounter))

	eventLeftCounter = 0
	eventRightCounter = 0

# Interrupt encoder functions
def myLeftCounterIT(LEFT_IT):

	global eventLeftCounter

	encoderA = io.input(LEFT_A)
	encoderB = io.input(LEFT_B)

	if (encoderA and not encoderB):
	        eventLeftCounter += 1

	if (not encoderA and encoderB):
	        eventLeftCounter -= 1


def myRightCounterIT(RIGHT_IT):

	global eventRightCounter

	encoderA = io.input(RIGHT_A)
	encoderB = io.input(RIGHT_B)

	if (encoderA and not encoderB):
	        eventRightCounter + 1

	if (not encoderA and encoderB):
	        eventRightCounter - 1



# Set the socket with server
s = socket.socket()
host = '10.42.0.1'# ip of bugro's PC
port = 1300

try:
    s.connect((host,port))

except:
    print("Unable to connect to server.\nCheck if IP address is correct and your firewall")

# Set the signal handler and a 5-second alarm

io.add_event_detect(LEFT_IT, io.FALLING, callback=myLeftCounterIT)
io.add_event_detect(RIGHT_IT, io.FALLING, callback=myRightCounterIT)

a = MyTimer(0.05, timer_handler)



# Main Program

try:
        print(str(s.recv(1024)))
	a.start()

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
	a.stop()
        print("\nEnd of Program\n")
        print("\nYou've been disconnected")
        s.close()




