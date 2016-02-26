
import socket
import datetime
import time
import signal, os
import RPi.GPIO as io
io.setmode(io.BCM)
io.setwarnings(False)

eventLeftCounter = 0
eventRightCounter = 0
tmp = 0
tmp1 = 0
tmp2 = 0

LEFT_PWM = 18
RIGHT_PWM = 19

LEFT_IT = 17
LEFT_A = 27
LEFT_B = 22

RIGHT_IT = 16
RIGHT_A = 20
RIGHT_B = 21

def timer_handler():
	
	global tmp
	global tmp1
	global tmp2
	global eventLeftCounter
	global eventRightCounter

	tmp1 = eventLeftCounter
	tmp2 = eventRightCounter
	eventLeftCounter = 0
	eventRightCounter = 0
	tmp = True

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


#Set up RPi.GPIO Pi

io.setup(LEFT_PWM, io.OUT)
pwm_left = io.PWM(LEFT_PWM, 4000)
pwm_left.ChangeFrequency(20000)
pwm_left.start(50)

io.setup(RIGHT_PWM, io.OUT)
pwm_right = io.PWM(RIGHT_PWM, 4000)
pwm_right.ChangeFrequency(20000)
pwm_right.start(50)

io.setup(LEFT_A, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(LEFT_B, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(RIGHT_A, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(RIGHT_B, io.IN, pull_up_down=io.PUD_DOWN)


# Set timer_handler

t = Timer(0.05, timer_handler)
t.start() # after 50 milliseconds

io.add_event_detect(LEFT_IT, io.FALLING, callback=myLeftCounterIT)
io.add_event_detect(RIGHT_IT, io.FALLING, callback= myRightCounterIT)


# Main Program

try:
	while(True):
		if(tmp):
			tmp = False;
			print "Droite : ",tmp1
			print "Gauche : ",tmp2

except:
	pwm_left.stop()         # stop the white PWM output
	pwm_right.stop()        # stop the red PWM output
	io.cleanup()            # clean up GPIO on CTRL+C exit
	print("\nEnd of Program")


