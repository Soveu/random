hello: hello.o main.o
	ld -g hello.o main.o -o hello 

hello.o: hello.asm
	yasm -f elf64 -g dwarf2 hello.asm -l hello.lst

main.o: main.asm
	yasm -f elf64 -g dwarf2 main.asm -l main.lst

clear:
	rm hello.o hello hello.lst main.o main.lst

nodebug:
	yasm -f elf64 main.asm \
	&& yasm -f elf64 hello.asm \
	&& ld hello.o main.o -o hello 
