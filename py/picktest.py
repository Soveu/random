#!/usr/bin/python

import pickle

class Program(object):
    def __init__(self, x):
        self.data = x
        return

    def run(self):
        return print(self.data)

x = Program("Hello")
print(pickle.dumps(x))

