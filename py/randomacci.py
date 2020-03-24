import random

N = 200000

s = [random.random() for i in range(N)]

s[0] = 1
s[1] = 1

for i in range(2, N):
    if s[i] < 0.5:
        s[i] = s[i-1] + s[i-2]
    else:
        s[i] = s[i-1] - s[i-2]

#print(s[-1])
#print()
#print(s[-2])
#print()
#print(s[-3])

print(s[-1] / s[-2])
print(s[-2] / s[-3])

