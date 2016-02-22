## Echo server program
#import socket
#
#HOST = ''                 # Symbolic name meaning all available interfaces
#PORT = 22              # Arbitrary non-privileged port
#s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#s.bind((HOST, PORT))
#s.listen(1)
#conn, addr = s.accept()
#print 'Connected by', addr
#while 1:
#    data = conn.recv(1024)
#    if not data: break
#    conn.sendall(data+"coucou")
#conn.close()

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
            data = c.recv(1024)
            print(data)
            if not data: break
            c.send("It is "+data)
    except:
        print("No connexion from client")
        c.close()