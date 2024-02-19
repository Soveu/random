import sys

def nwd(a, b):
    if b == 0:
        return a

    return nwd(b, a % b)

def cane(n):
    nom = ((n-1)**2) * (n+3) * (n-2) // 2
    denom = n**3

    nom += n**2
    nom += (2*n*(n-1))
    n = nwd(nom, denom)
    return nom // n, denom // n

n = int(sys.argv[1])
a, b = cane(n)
p = (a * 1000) // b
e = p // n
print(e, p, a, b)

