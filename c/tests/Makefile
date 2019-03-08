CC=g++
FLAGS=-g

out: main.o pipedchild.o
	$(CC) main.o pipedchild.o -o out $(FLAGS)

main.o: main.c
	$(CC) main.c -c $(FLAGS)

pipedchild.o: pipedchild.c
	$(CC) pipedchild.c -c $(FLAGS)

clean:
	rm pipedchild.o main.o out
