#!/usr/bin/env python
import socket
import time

host = '127.0.0.1'
port =  10433
times = 64


def main():
    global times
    while times > 0:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((host, port))
        sock.send("hello?");
        data = sock.recv(1024);
        print 'receive: ', data
        sock.close()
        times = times - 1
    print 'done ', times
if __name__ == '__main__':
    main()
