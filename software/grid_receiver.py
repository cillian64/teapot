#!/usr/bin/env python3

import serial
import sys
import numpy as np
import grid_decode
import time
import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt

default_serial = "/dev/cu.usbmodem401"

if len(sys.argv) == 2:
    default_serial = sys.argv[1]
else:
    print("Using default serial port: {}".format(default_serial))

ser = serial.Serial(default_serial)

allbytes = bytearray([0]*128)
pixels = [0]*64
array = np.zeros((8, 8))
# Set initial scale from 20-30 celcius.
array[:] = 20
array[1] = 30

im = plt.imshow(array, cmap=plt.get_cmap("coolwarm"), interpolation="none")
plt.colorbar()
plt.ion()
plt.show()

while True:
    line = ser.readline()[:-1].decode('utf-8')
    if not line.endswith("[TEAx]"):
        plt.pause(0.1)
        continue

    # Extract comment portion of packet:
    line = line[line.find(":")+1:line.find("[")]
    average, centre, pixels = grid_decode.decode(line)

    for y in range(8):
        for x in range(8):
            idx = 8 * y + x
            array[7-y, 7-x] = pixels[idx]
            print("{:2.2f} ".format(pixels[idx]), end="")
            if (idx+1) % 8 == 0:
                print("")

    print("Centre: {:.2f}°C".format(centre))
    print("Average: {:.2f}°C".format(average))
    print("")

    im.set_data(array)
#    im.autoscale()
    plt.draw()
    plt.pause(0.1)
