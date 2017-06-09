import os
import time
import sys
import serial
ser = serial.Serial('COM3', 250000)  # open serial port
print(ser.name)         # check which port was really used
connect = False
li = list()
try:
    while True:
        sys.stdout.flush()
        if not connect:
            line = ser.read()
            print('arduino: ', line)
            if line == b'a':
                ser.write(b'a')
                connect = True
                print('python: start working')
            print('python: connected')
        if connect:
            ser.write(b'R')
            # print('python: send b"R"')
            line = ser.readline().decode('utf-8')
            print(line)
            # time.sleep(0.1)
except KeyboardInterrupt as e:
    ser.close()
    exit()
