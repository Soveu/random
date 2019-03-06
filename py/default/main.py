#!/usr/bin/python2

class Foo:
    def __init__(self, br=0, bz={}):
        self.bar = br
        self.baz = bz

if __name__ == '__main__':
    f1 = Foo();
    f2 = Foo();

    f2.baz["l33t"] = "h4x0r"
    assert(f1.baz == f2.baz)

    f2.bar += 1;

    for f in f1, f2:
        print repr(f.baz) + str(f.bar)
