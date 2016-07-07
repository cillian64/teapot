#!/usr/bin/python3

import serial
import sys
import requests

default_serial = "/dev/ttyACM2"

if len(sys.argv) == 2:
    default_serial = sys.argv[1]
else:
    print("Using default serial port: {}".format(default_serial))

ser = serial.Serial(default_serial)

while True:
    line = ser.readline()[:-1]  # Chop trailing \n
    print(line.decode('utf-8'))

    requests.post('http://www.ukhas.net/api/upload', data = {
        'origin': 'TEA0',
        'data': line})

