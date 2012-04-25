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
sys.path.append('lib/')
from charter_client import Client

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


