import random

samo = 'euioa'
spol = 'qwrtpsdfghjklmnbvcxz'

name = ''

n = random.randint(4, 10)
x = random.randint(0, 1)
for i in range(n):
    if i % 2 == x:
        name += random.choice(samo)
    else:
        name += random.choice(spol)

print(name)

