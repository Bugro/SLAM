# -*- coding: utf-8 -*-
"""
Created on Fri Feb 26 10:00:52 2016

@author: guill
"""

import socket

s = socket.socket()
host = '' #Symbolic name meaning all available interfaces
port = 1300
s.bind((host, port))

s.listen(5)

while True:
    c, addr = s.accept()
    print ('Got connection from',addr)
    c.send('Thanks for connecting\n')
    try:
        while True:
            cmd = str(raw_input())
#            cmd = msvcrt.getche() #Commande pour Windows permettant de ne pas appuyer sur Enter
            if cmd == 'z':
                c.send("R=100")
                c.send("L=100")
            elif cmd == 'd':
                c.send("R=-100")
                c.send("L=100")
            elif cmd == 'q':
                c.send("R=100")
                c.send("L=-100")
            else:
                c.send("R=50")
                c.send("L=50")
    except:
        print("No connexion from client")
        c.close()