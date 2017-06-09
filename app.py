import serial
import os
ser = serial.Serial('COM3', 115200)  # open serial port
print(ser.name)         # check which port was really used
# ser.write(b'hello')     # write a string
acc = [0, 0, 0, 2, 0, 0]
ypr = [0, 0, 0, 2, 0, 0]
try:
    while True:
        line = ser.readline()
        try:
            a = line.decode('utf-8').split('\t')
            # print(len(a))
            # print(a)
            if len(a) == 4:
                # if a[0] == 'ACC':
                #     print(a)
                #     acc = a[1:]
                #     acc[-1] = acc[-1][0:-2]
                #     acc = list(map(lambda x: int(x) / 100.0, ypr))

                if a[0] == 'YPR':
                    ypr = a[1:]
                    ypr[-1] = ypr[-1][0:-2]
                    ypr = list(map(lambda x: int(x) / 100.0, ypr))
        except:
            pass

            # print(line.decode("utf-8"))
            # os.system('cls')
        print('acc      {}   {}     {}  ypr      {}      {}       {}'.format(
            *acc, * ypr))
except KeyboardInterrupt as e:
    ser.close()
    exit()
