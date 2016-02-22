
import socket
import datetime
import time

s = socket.socket()
host = '169.254.21.120'# ip of the computer
port = 1300
try:
        s.connect((host,port))
except:
        print("Unable to connect to server.\nCheck if IP address is correct and your firewalirewall options.")


try:
    while(1):
        date = str(datetime.datetime.now())
        s.sendall(date)
        print(s.recv(1024))
        time.sleep(1)
except:
        print("\nYou've been disconnected")
        s.close()
