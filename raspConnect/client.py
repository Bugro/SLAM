# -*- coding: utf-8 -*-
"""
Created on Thu Feb 25 10:27:26 2016

@author: guill
"""


import socket
import datetime
import time
import RPi.GPIO as io
io.setmode(io.BCM)

in1_pin = 18
in2_pin = 19

io.setup(in1_pin, io.OUT)
io.setup(in2_pin, io.OUT)

p1 = io.PWM(in1_pin, 4000)
p1.start(0)
p2 = io.PWM(in2_pin, 4000)
p2.start(100)

pause_time = 0.02

s = socket.socket()
host = '169.254.21.120'# ip of bugro's PC
#host = '169.254.179.113'# ip of robot's raspberry
port = 1100
try:
    s.connect((host,port))
except:
    print("Unable to connect to server.\nCheck if IP address is correct and your firewall")


try:
        print s.recv(1024)
        s.sendall("OK")
        while True:
                data =  int(s.recv(1024))
                print data
                p1.ChangeDutyCycle(float(data))
                p2.ChangeDutyCycle(float(data))
                time.sleep(1)
except:
        p1.stop()            # stop the white PWM output
        p2.stop()              # stop the red PWM output
        io.cleanup()          # clean up GPIO on CTRL+C exit
        print("\nYou've been disconnected")
        s.close()


