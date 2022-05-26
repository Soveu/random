import sys

s = sys.stdin.read()

for c in " .,?!:;()'\"`“’":
    s = s.replace(c, '')

print(s)
