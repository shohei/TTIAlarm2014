#! /usr/bin/python

#    Serial Reader for ARDUINO
#    usefull when tail -f /dev/ttyXXXX doesn't work
#
#    Change ttyACM0 for your own tty interface

import serial
import time
import commands

# The second argument is the baudrate, change according to the baudrate you gave to your Serial.begin command
status,output= commands.getstatusoutput("ls /dev/tty.usb*")
sport = output
ser = serial.Serial(sport, 9600)

# To avoid communication failure due to bad timings
ser.setDTR(True);
time.sleep(1);
ser.setDTR(False)

while True:
    print ser.readline()
