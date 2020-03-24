def f(p):
    res = 0
    for i in range(1, 10000):
        x = 1 - p**i
        x *= p ** ((i-1)*i // 2)
        res += i * x
    return res

def g(p):
    res = 0
    for i in range(1, 10000):
        res += i * (1-p) * p ** (i-1)
    return res

