def foo(number: int) -> int:
#    assert isinstance(number, foo.__annotations__["number"]), "Oh no!"
    print(f'Nice number "{number}"! I\'ll double it!')
    return number * 2

print(foo(2))
print(foo('bar'))

print(foo.__annotations__)
print(foo.__dict__)

