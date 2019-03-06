#!/usr/bin/python

# list() here doesnt create a unique list, x behaves like a static variable
def func(x=list()):
    x.append(len(x))

    # return a copy
    return list(x)

# The variable is not shared across more functions
def func2(x=[]):
    x.append(len(x))
    return x

if __name__ == '__main__':
    x1 = func()
    x2 = func()

    x2.append("foo")
    x2.append("bar")
    func()
    x3 = func()

    for x in x1,x2,x3:
        print(x)
