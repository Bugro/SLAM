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
    synchro = c.recv(1024)
    print(synchro)
    try:
        while True:
            
            data = str(raw_input("Vitesse"))
            c.send(data)
    except:
        print("No connexion from client")
        c.close()