import serial
import threading

def receiverHander():
    while(True):
        response = ser.readline()
        print(response);

ser = serial.Serial("COM41",115200)  # open serial port
print(ser.name)         # check which port was really used
ser.write(b'Hi')     # write a string


t = threading.Thread(target=receiverHander())
t.start();