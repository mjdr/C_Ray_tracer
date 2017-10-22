
CC=gcc -L/usr/lib/x86_64-linux-gnu/

all: make run


make: clear compile
	
compile:
	$(CC) -c *.c
	
	$(CC) -o main main.o -lm 
run:
	./main

clear:
	rm -f main
	rm -f *.o
