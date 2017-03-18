#!/usr/bin/env python3

import serial
import sys
import requests

default_serial = "/dev/cu.usbmodem401"

if len(sys.argv) == 2:
    default_serial = sys.argv[1]
else:
    print("Using default serial port: {}".format(default_serial))

ser = serial.Serial(default_serial)

while True:
    line = ser.readline()[:-1]  # Chop trailing \n
    print(line.decode('utf-8'))

    # See if it looks like a ukhn packet before uploading
    hops = line.decode('utf-8')[0]
    seq = line.decode('utf-8')[1]
    if hops >= '0' and hops <= '9' and seq >= 'a' and seq <= 'z':
        requests.post('http://www.ukhas.net/api/upload', data={
            'origin': 'TEA0',
            'data': line})
