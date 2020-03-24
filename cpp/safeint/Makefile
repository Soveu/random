program: main.c asm.o
	g++ asm.o main.c -o program

asm.o: amd64.asm
	yasm -f elf64 amd64.asm -o asm.o

