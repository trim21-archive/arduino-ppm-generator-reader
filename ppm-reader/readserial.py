import os
import time
import sys
import serial
ser = serial.Serial('COM3', 9600)  # open serial port
print(ser.name)         # check which port was really used
connect = False
li = list()
try:
    while True:
        sys.stdout.flush()
        line = ser.readline()
        print(line)
except KeyboardInterrupt as e:
    ser.close()
    exit()
