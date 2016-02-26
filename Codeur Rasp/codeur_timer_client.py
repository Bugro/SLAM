
import socket
import datetime
import time
import signal, os
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

def timer_handler(signum, frame):
	
	global eventLeftCounter
	global eventRightCounter
	
	s.sendall(eventLeftCounter)
	s.sendall(eventRightCounter)

	eventLeftCounter = 0
	eventRightCounter = 0


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

# Set the socket with server
s = socket.socket()
host = '169.254.21.120'# ip of bugro's PC
port = 1100

try:
    s.connect((host,port))
except:
    print("Unable to connect to server.\nCheck if IP address is correct and your firewall")


# Set the signal handler and a 5-second alarm
signal.signal(signal.SIGALRM, timer_handler)
signal.alarm(5)

io.add_event_detect(LEFT_IT, io.FALLING, callback=myLeftCounterIT)
io.add_event_detect(RIGHT_IT, io.FALLING, callback= myRightCounterIT)
	
	
# Main Program
try:
	print s.recv(1024)
	s.sendall("OK")

	while True:
		data =  int(s.recv(1024))
		pwm_left.ChangeDutyCycle(float(data))
		pwm_right.ChangeDutyCycle(float(data))
		time.sleep(1)

except:
	pwm_left.stop()         # stop the white PWM output
	pwm_right.stop()        # stop the red PWM output
	io.cleanup()            # clean up GPIO on CTRL+C exit
	print("\nEnd of Program")
	print("\nYou've been disconnected")
	s.close()

