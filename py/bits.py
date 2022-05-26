
def step(x, y, A):
    nx = (x & ~A) | (~y & A)
    ny = (y & ~A) | (~y & x & A)
    return (nx, ny)

test = [3, 4, 3, 3, 4, 4, 6]

x = 0
y = 0

for a in test:
    x, y = step(x, y, a)

print(x, y)
