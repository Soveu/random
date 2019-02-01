#!which python
import random

samogloski = "aeiouy"
spolgloski = "qwrtplkjhgfdszxcvbnm"

nicklen = random.randint(4, 7)
beg = (nicklen % 2 == 1)

for i in range(nicklen):
    if beg:
        letter = random.choice(samogloski)
    else:
        letter = random.choice(spolgloski)

    beg = not beg
    print(letter, end='', flush=False)

print()

