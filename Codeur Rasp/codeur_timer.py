
import time
import threading
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
pwm_left.start(70)

io.setup(RIGHT_PWM, io.OUT)
pwm_right = io.PWM(RIGHT_PWM, 4000)
pwm_right.ChangeFrequency(20000)
pwm_right.start(70)

io.setup(LEFT_A, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(LEFT_B, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(RIGHT_A, io.IN, pull_up_down=io.PUD_DOWN)
io.setup(RIGHT_B, io.IN, pull_up_down=io.PUD_DOWN)


# Set the signal handler and a 5-second alarm

io.add_event_detect(LEFT_IT, io.FALLING, callback=myLeftCounterIT)
io.add_event_detect(RIGHT_IT, io.FALLING, callback= myRightCounterIT)


# Main Program

try:
	a = MyTimer(0.05, timer_handler) 
	a.start() 

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


