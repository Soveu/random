SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
CCFLAGS=-O2
CCDEBUGFLAGS=-ggdb -fsanitize=address
CC=g++

grow: main.cpp
	$(CC) main.cpp -o grow $(CCFLAGS) $(SFMLFLAGS)
debug: main.cpp
	$(CC) main.cpp -o grow $(CCDEBUGFLAGS) $(SFMLFLAGS)
