CC=gcc
CFLAGS= -g -std=c11 -pedantic -Wall -Wextra
LIBS= -lm
all:scanner

run:scanner

scanner.o:scanner.c
	$(CC) $(CFLAGS)  scanner.c -o scanner.o $(LIBS)

clean:
	rm *.o scanner
