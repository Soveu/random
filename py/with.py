class Door():
    def __enter__(self):
        print("*Door squeaking*")

    def __exit__(self, a, b, c):
        print(f"Closing the door with args: {a}, {b}, {c}")

with Door() as d:
    pass

