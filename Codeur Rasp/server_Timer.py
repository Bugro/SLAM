# -*- coding: utf-8 -*-
"""
Created on Fri Feb 26 10:00:52 2016

@author: guill
"""

import socket
import threading
import time

def test():
	c.send(time.strftime('%d/%m/%y %H:%M:%S:%U',time.localtime())) 

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

s = socket.socket()
host = '' #Symbolic name meaning all available interfaces
port = 1300
s.bind((host, port))

s.listen(5)

while True:
	c, addr = s.accept()
	print ('Got connection from',addr)
	c.send('Thanks for connecting\n')

	a = MyTimer(1.0, test) 
	a.start() 

	try:  
		while True:
			pass            

	except:
		print("No connexion from client")
		a.stop()
		c.close()
		s.close()
