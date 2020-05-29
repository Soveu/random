#!/usr/bin/python3

"""
Results:
--- Remove if number is evenly dividable by 2
1.2708177
1.2841774
0.667672

--- Remove if number is evenly dividable by 3
1.3165607
1.1905327999999997
0.6251088999999999

--- Remove if number is evenly dividable by 4
1.2822456
1.0946345
0.6509212999999998
"""

TESTSNO = 1000
N = 10000
def test1():
    x = list(range(N))
    y = list(filter(lambda a: a % 4 != 0, x))
    x.clear()
    x.extend(y)

def test2():
    x = list(range(N))
    for i, item in enumerate(x):
        if item % 4 == 0:
            x.pop(i)

def test3():
    x = list(range(N))
    y = [a for a in x if a % 4 != 0]
    x.clear()
    x.extend(y)

def testx():
    v = list(range(N))
    i = 0
    
    while i < len(v):
        if v[i] % 4 == 0:
            i += 1
            continue
    
        v[i], v[-1] = v[-1], v[i]
        v.pop()

def test4():
    x = list(range(N))
    for item in x:
        while item % 4 != 0:
            item, x[-1] = x[-1], item
            x.pop()

def test5():
    x = list(range(N))
    i = 0
    end = len(x)

    while i < end:
        if x[i] % 4 == 0:
            i += 1
            continue

        end -= 1
        x[i], x[end] = x[i], x[end]


def test6():
    x = list(range(N))
    begin = iter(x)
    end = reversed(x)

if __name__ == '__main__':
    import timeit
    print(timeit.timeit("test3()", setup="from __main__ import test3", number=TESTSNO))
    print(timeit.timeit("test4()", setup="from __main__ import test4", number=TESTSNO))
    print(timeit.timeit("test5()", setup="from __main__ import test5", number=TESTSNO))
