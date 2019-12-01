#!/usr/bin/python

import random, math

while True:
    socks = [0.0, 0.0, 0.0, 0.0]
    
    for _ in range(43):
        sock = random.randint(0,3)
        socks[sock] += 0.5
    
    pairs = 0
    for s in socks:
        pairs += math.floor(s)
    
    if pairs < 20:
        print("YOUR PROOF IS WRONG")
        exit()

