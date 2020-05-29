def testx():
    v = list(range(1000))
    i = 0
    
    while i < len(v):
        if v[i] % 4 == 0:
            i += 1
            continue
    
        v[i], v[-1] = v[-1], v[i]
        v.pop()

print(v)
print(len(v))
