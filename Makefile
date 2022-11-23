PROJ=proj
FILES=syntactic.c scanner.c gramatic_rules.c buffer.c token_buffer.c syntactic_stack.c expression.c symtable.c
CC=gcc
CFLAGS= -g -std=c11 -pedantic -Wall -Wextra -pthread


all : $(PROJ)

$(PROJ) : $(FILES)
			$(CC) -g $(CFLAGS) -o $(PROJ) $(FILES) -lm

clean:
	rm proj
