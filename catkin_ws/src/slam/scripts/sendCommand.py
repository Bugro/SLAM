#!/usr/bin/env python

import socket

s = socket.socket()
host = '' #Symbolic name meaning all available interfaces
port = 1300
s.bind((host, port))

s.listen(5)

while True:
    c, addr = s.accept()

    print ('Got connection from',addr)
    c.send('Connecting to slam\n')

    try:
        while True:
		cmd = input()
		print(cmd + "\n")
		if cmd == 'z':
            		c.send("R="+255)
			c.send("L="+255)
		elif cmd == 'd':
                        c.send("R=-"+128)
                        c.send("L="+128)
                elif cmd == 'q':
			c.send("R="+128)
                        c.send("L=-"+128)
		else:
			c.send("R=-"+0)
                        c.send("L="+0)

    except:
        print("No connexion from client")
        c.close()
