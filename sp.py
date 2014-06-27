#!/usr/bin/env python
#-*- coding:utf-8 -*-

import serial
import threading
import sys
import commands

try:
    status, output = commands.getstatusoutput("ls /dev/tty.usb*")
    dev_port = output
    s = serial.Serial(port=dev_port,baudrate=9600)
except:
    print "No usb device found."
    exit()

s.setDTR(True);
time.sleep(1);
s.setDTR(False)

def thread2():
    while True:
        data = s.read()
        sys.stdout.write(data)

t2 = threading.Thread(target=thread2)
t2.start()

#print "Press <Enter> to exit."
#print "Wait a moment for initializing......"
while(True):
    try:
        key = raw_input()
        if(key==""):
            t2._Thread__stop()
            exit()
        key += "\n"
        s.write(key)
    except:
        print "\nstop thread2"
        t2._Thread__stop()
        exit()
