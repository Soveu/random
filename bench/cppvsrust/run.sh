#!/bin/bash

INPUTFILE=/dev/shm/input

echo -----------------
echo TESTING TREE SETS
echo -----------------
echo Rust
time ./btree < $INPUTFILE
echo -----------------
echo C++
time ./cppset < $INPUTFILE
echo -----------------

echo -----------------
echo TESTING HASH SETS
echo -----------------
echo Rust
time ./hash < $INPUTFILE
echo -----------------
echo C++
time ./cppunorderedset < $INPUTFILE
echo -----------------

