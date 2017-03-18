#!/usr/bin/env python3

import serial
import sys
import numpy as np
import grid_decode
import time
import socket
import json
import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt


def do_packet(packet, im):
    # Extract comment portion of packet:
    print("packet is {}".format(packet))
    packet = packet[packet.find(":")+1:packet.find("[")]
    print("comment is {}".format(packet))
    average, centre, pixels = grid_decode.decode(packet)

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


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: {} source".format(sys.argv[0]))
        print("source can be a serial port (e.g. /dev/cu.usbmodem401)")
        print("or `ukhn' to read from the ukhas.net stream")
        sys.exit(1)

    if sys.argv[1] == "ukhn":
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect(("ukhas.net", 3020))
        source = sock.makefile()
    else:
        source = serial.Serial(sys.argv[1])

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
        line = source.readline()[:-1]
        if not isinstance(line, str):
            line = line.decode('utf-8')
        if sys.argv[1] == "ukhn":
            line = json.loads(line)['p']
        node = line[line.find('[')+1:]
        node = node[:node.find(',')]
        if node[:3] != "TEA":
            plt.pause(0.1)
            continue
        do_packet(line, im)
