#!/usr/bin/python

def avg(arr):
    return sum(arr)/len(arr)

def avgplus(a, n, x):
    bx = (x-a) / (n+1)
    return a+bx

if __name__ == '__main__':
    t = int(input("Enter a number: "))
    
    arr = [1,2,3]
    
    a = avg(arr)
    
    x1 = avgplus(a, len(arr), t)
    
    arr.append(t)
    x2 = avg(arr)
    
    print(x1, x2)

