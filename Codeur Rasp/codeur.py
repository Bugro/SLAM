

import time
import RPi.GPIO as io
io.setmode(io.BCM)
io.setwarnings(False)

eventLeftCounter = 0
eventRightCounter = 0

LEFT_PWM = 18
RIGHT_PWM = 19

LEFT_IT = 17
LEFT_A = 27
LEFT_B = 22

RIGHT_IT = 16
RIGHT_A = 20
RIGHT_B = 21

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

#io.setup(LEFT_IT, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(LEFT_A, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(LEFT_B, io.IN, pull_up_down=io.PUD_DOWN)

#io.setup(RIGHT_IT, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(RIGHT_A, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(RIGHT_B, io.IN, pull_up_down=io.PUD_DOWN)

io.add_event_detect(LEFT_IT, io.RISING, callback=myLeftCounterIT)
io.add_event_detect(RIGHT_IT, io.RISING, callback=myRightCounterIT)

# Main Program

try:
	while(True):
		print eventRightCounter,"\n"
		print eventLeftCounter,"\n"
		eventLeftCounter = 0
		eventRightCounter = 0
		time.sleep(1)
except:
	io.cleanup()            # clean up GPIO on CTRL+C exit
	print("\nEnd of Program")


