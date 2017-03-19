#!/usr/bin/env python3

import socket
import json


if __name__ == "__main__":
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(("ukhas.net", 3020))
    source = sock.makefile()

    seen = set()
    while True:
        line = source.readline()[:-1]
        line = json.loads(line)['p']
        node = line[line.find('[')+1:]
        node = node[:node.find(',')]
        if node[:3] != "TEA":
            continue
        if hash(line) not in seen:
            seen.add(hash(line))
            print(line)
