
def f(a,b):
    print(hex(id(a)), hex(id(b)))
    a += 'asdf'
    b += 'qwerty'
    print(hex(id(a)), hex(id(b)))
    print('--------------------')
    return a.endswith('asdf')

assert f('', '')
s = 'aewoijfwe'
assert f(s, s)

