
a = list(range(3))
b = list(range(7))

aiter = iter(a)
biter = iter(b)

print("Zipped:")
for x,y in zip(biter, aiter):
    print(x,y)

print("aiter:")
for x in aiter:
    print(x)

print("biter:")
for x in biter:
    print(x)


