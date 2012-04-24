import os,sys,string,socket
import time

class Chart(object):

    def __init__(self, name, ch=None):
        """
        Receives:  data_points -- A list of DataPoint objects
                   name -- The 'name' of the series
                   ch(optional) -- an existing chart client object to talk to
        """
        if (ch == None):
            self.ch = Client()
        else:
            self.ch = ch

        self.data_points = []
        self.name = name

    def append(self, x, y):
        """
        Add a data point to our internal list
        Receives: x and y values for data point
        """
        self.data_points.append((x,y))

    def plot(self):
        """
        Call needed client functions to send chart data to Charter application
        """
        plot_string = " ".join(map(lambda n: "%s,%s" % n, self.data_points))

        self.deliver("m " + plot_string)


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
