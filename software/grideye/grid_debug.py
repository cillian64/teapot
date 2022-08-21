#!/usr/bin/env python3

import serial
import sys
import grid_decode

default_serial = "/dev/cu.usbmodem401"

if len(sys.argv) == 2:
    default_serial = sys.argv[1]
else:
    print("Using default serial port: {}".format(default_serial))

ser = serial.Serial(default_serial)

while True:
    line = ser.readline()[:-1]  # Chop trailing \n
    line = line.decode('utf-8')
    if not line.endswith("[TEAx]"):
        continue
    line = line[line.find(":")+1:]
    line = line[:line.find("[")]

    average, centre, pixels = grid_decode.decode(line)

    print("average: {}°C".format(average))
    print("centre: {}°C".format(centre))
    for idx, b in enumerate(pixels):
        print("{:2.2f} ".format(b), end="")
        if (idx+1) % 8 == 0:
            print("")
    print("")
