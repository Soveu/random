hello: hello.o
	ld -N hello.o -o hello

hello.o: hello.asm
	yasm -f elf64 hello.asm

clear:
	rm hello.o hello
