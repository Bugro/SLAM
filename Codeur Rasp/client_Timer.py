# -*- coding: utf-8 -*-
"""
Created on Thu Feb 25 10:27:26 2016

@author: guill
"""

import socket
import time

s = socket.socket()
host = '127.0.1.0'# ip of bugro's PC
#host = '169.254.179.113'# ip of robot's raspberry
port = 1300

try:
    s.connect((host,port))

except:
    print("Unable to connect to server.\nCheck if IP address is correct and your firewall")

print(s.recv(1024))

try:
	while True:
		data = str(s.recv(1024))
		print data		
except:
	print("\nYou've been disconnected")
	s.close()
