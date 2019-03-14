#!/usr/bin/python2

import subprocess
import sys
import time

sh = '/bin/bash'

p = subprocess.Popen(
                     [sh], 
                     bufsize=4096, 
                     stdin=subprocess.PIPE, 
                     stderr=subprocess.PIPE, 
                     stdout=subprocess.PIPE)

p.stdin.write("sleep 1; echo Hello\n")
time.sleep(1)
print p.poll()
stdout, stderr = p.communicate()

print stdout
print "----------"
print stderr

