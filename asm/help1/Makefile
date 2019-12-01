progr: progr.o
	ld progr2.o -o progr2

progr.o: progr.asm
	yasm -f elf64 -g dwarf2 progr2.asm

clear:
	rm progr.o progr

