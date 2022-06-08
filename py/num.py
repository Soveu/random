import copy

def gcd(a, b):
    while b != 0:
        a, b = b, a % b

    return a

class Int:
    def __init__(self, x):
        self.x = x

    def __repr__(self):
        return f"Int({self.x})"

    def add(self, rhs):
        if type(rhs) == Int:
            return Int(self.x + rhs.x)

        raise Exception

    def mul(self, rhs):
        if type(rhs) == Int:
            return Int(self.x * rhs.x)

        raise Exception

    def sub(self, rhs):
        if type(rhs) == Int:
            return Int(self.x - rhs.x)

        raise Exception


    def div(self, rhs):
        if type(rhs) == Int:
            return self.div_int(rhs)
        if type(rhs) == Div:
            return rhs.div_int(self)

        raise Exception

    def div_int(self, rhs):
        if self.x % rhs.x == 0:
            return Int(self.x // rhs.x)

        g = gcd(self.x, rhs.x)
        return Div(Int(self.x // g), Int(rhs.x // g))


class Add:
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs

    def __repr__(self):
        return f"Add({self.lhs}, {self.rhs})"


class Sub:
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs

    def __repr__(self):
        return f"Sub({self.lhs}, {self.rhs})"


class Div:
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs

    def __repr__(self):
        return f"Div({self.lhs}, {self.rhs})"

    def div(self, rhs):
        if type(rhs) == Int:
            return self.div_int(rhs)

        raise Exception

    def div_int(self, rhs):
        if type(self.lhs) == Int:
            g = gcd(rhs.x, self.lhs.x)
            return Int(self.lhs.x // g).div(self.rhs.mul(Int(rhs.x // g)))

        if type(self.lhs) == Mul:
            lhs = copy.deepcopy(self.lhs)
            tmp = rhs.x

            if type(lhs.lhs) == Int:
                g = gcd(tmp, lhs.lhs.x)
                lhs.lhs.x //= g
                tmp //= g

            if type(lhs.rhs) == Int:
                g = gcd(tmp, lhs.rhs.x)
                lhs.rhs.x //= g
                tmp //= g

            return Div(lhs, self.rhs.mul_int(tmp))

        raise Exception

class Mul:
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs
    
    def __repr__(self):
        return f"Mul({self.lhs}, {self.rhs})"


expr = Int(5).div(Int(3))
print(expr)
expr = Int(24).div(Int(18))
print(expr)
expr = Int(24).div(Int(6))
print(expr)
expr = Int(24).div(Int(4)).div(Int(8))
print(expr)
expr = expr.div(Int(6))
print(expr)
