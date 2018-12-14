from socket import *
s = socket(AF_INET, SOCK_DGRAM)
s.bind( ('', 5555))

while(True):
    m = s.recvfrom(1024)
    if(len(m)!=0):
        print(m)
