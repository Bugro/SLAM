# -*- coding: utf-8 -*-
"""
Created on Fri Feb 26 10:00:52 2016

@author: guill
"""

import socket

s = socket.socket()
host = '' #Symbolic name meaning all available interfaces
port = 1100
s.bind((host, port))

s.listen(5)

while True:
    c, addr = s.accept()
    print ('Got connection from',addr)
    c.send('Thanks for connecting\n')
    try:
        while True:
		print str(s.recv(1024))
    except:
        print("No connexion from client")
        c.close()
