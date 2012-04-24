#! /usr/bin/python
'''
(C) 2011 by Ilia Greenblat
charting using Paolo Bosetti Charter.
using Charter with python
activation:    python  charter_client.py 
or just charter_client.py  if the first line in this script works.
'''

import os,sys,string,socket
import time

class Client:
    def __init__(self):
        self.BASE=2000
        self.id=1
        self.host='127.0.0.1'
        self.delay = 0.005

    def array1(self,Array):
        res='s '
        for X in Array:
            res += '  %s'%str(X)
        self.deliver(res)
        
    def clear(self):
        self.deliver('CLEAR')
    def close(self):
        self.deliver('CLOSE')
    def names(self,Names):
        self.deliver('NAMES ' + Names)
    def names(self,Labels):
        self.deliver('NAMES ' + Labels)

    def deliver(self,Str):
        Host = socket.gethostbyname(self.host)
        self.sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM,0)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.connect((Host, self.BASE+self.id))
        self.sock.send(Str)
        self.sock.close()
        time.sleep(self.delay)


# demo use
import random
def try_main():
    ch = Client()
    ch.id = 1
    for x in range(5):
        ch.clear()
        for i in range(100):
            ch.array1([i,random.randint(0,5),random.randint(10,15),random.randint(20,25)])
        ch.names('speed velocity acceleration')
        time.sleep(1)



if __name__ == '__main__':
    try_main()


