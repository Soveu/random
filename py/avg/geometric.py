#!/usr/bin/python

import math

def avg(arr):
    product=1

    for x in arr:
        product *= x

    return math.pow(product, 1/len(arr))

def avgplus(a, n, x):
    return a * math.pow(x/a, 1/(n+1))

if __name__ == '__main__':
    arr = [1,2,4]
    t = int(input())

    a = avg(arr)

    x1 = avgplus(a, len(arr), t)

    arr.append(t)
    x2 = avg(arr)

    print(x1, x2)

