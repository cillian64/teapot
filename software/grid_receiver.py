#!/usr/bin/python3

import serial
import sys
import requests
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

default_serial = "/dev/ttyACM2"

if len(sys.argv) == 2:
    default_serial = sys.argv[1]
else:
    print("Using default serial port: {}".format(default_serial))

ser = serial.Serial(default_serial)

allbytes = bytearray([0]*128)
pixels = [0]*64
array = np.zeros((8, 8))
array[:] = 80
array[0,0] = 120

fig = plt.figure()
ax = fig.add_subplot(111)
im = plt.imshow(array, cmap=plt.get_cmap("coolwarm"), interpolation="none")
plt.colorbar()
fig.show()

while True:
    # Sync to input signal:
    while True:
        while ser.read().decode('utf-8') != 'G':
            pass
        if ser.read().decode('utf-8') != 'R':
            continue
        if ser.read().decode('utf-8') != 'I':
            continue
        if ser.read().decode('utf-8') != 'D':
            continue
        packet_type = ser.read().decode('utf-8')
        if packet_type not in ['1', '2', '3']:
            continue
        break

    # Read correct number of bytes:
    if packet_type == '1' or packet_type == '2':
        packet = ser.read(43)
    else:
        packet = ser.read(42)

    strpacket = ' '.join([str(int(x)) for x in packet])
#    print("Packet type {}: {}".format(packet_type, strpacket))

    if packet_type == '1':
        allbytes[0:43] = packet
    elif packet_type == '2':
        allbytes[43:86] = packet
    elif packet_type == '3':
        allbytes[86:128] = packet

    for i in range(64):
        pixels[i] = allbytes[2*i+1]# + allbytes[2*i-1] * 2**8

    for x in range(8):
        for y in range(8):
            array[7-y,7-x] = pixels[8*y+x]

#    print(' '.join([str(int(x)) for x in pixels]))
#    print("")
    print(array)
    im.set_data(array)
#    plt.imshow(array, cmap=plt.get_cmap("coolwarm"))
    plt.draw()
