#!/bin/bash

names="zero jeden dwa trzy"
flags="-S -masm=intel main.cpp"
compilers="g++ clang++"

for compiler in $compilers; do
	counter=0
	for name in $names; do
		com="$compiler $flags -O$counter -o ${compiler}/${name}.asm"
		echo $com
		mkdir -p $compiler
		$com
		((counter++))
	done
done
