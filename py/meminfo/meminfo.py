#!/usr/bin/python

data = []

with open("/proc/meminfo", "r") as f:
    data = f.readlines()

total = int(data[0].split()[1])
maxlen = 0
entries = []

for line in data:
    (name, value) = line.split()[:2]
    value = 100.0 * int(value) / total
    maxlen = max(len(name), maxlen)
    entries.append((name, value))

maxlen += 1
formatstr = "{:%d}{:0.2f}" % maxlen

for entry in entries:
    print(formatstr.format(entry[0], entry[1]))

