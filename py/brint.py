import sys

def brint(*bytez, sep=b'', file=sys.stdout, flush=True):
    f = file.buffer
    f.write(sep.join(bytez))
    if flush:
        f.flush()

brint(b'asdf', b'qwety')

