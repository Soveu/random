import sys
import time

alphabet = "qwertyuiopasdfghjklzxcvbnm !?.,;:'\"[]{}=-0123456789@#$%^&*()`~QWERTYUIOPASDFGHJKLZXCVBNM"

def brute(text, sleeptime=0.02, flush=True, end='\n'):
    for c in text:
        for a in alphabet:
            sys.stdout.write(a)
            sys.stdout.flush()

            if a == c:
                break
            if c == '\n' or c == '\t' or c == '\r':
                sys.stdout.write(c)
                break
            
            sys.stdout.write("\b")
            time.sleep(sleeptime)

    sys.stdout.write(end)
    if flush:
        sys.stdout.flush()

t = 0.02

print("Login: ", end='')
brute("k2e16", t)
print("Password: ", end='')
brute("lolpass", t)
            
