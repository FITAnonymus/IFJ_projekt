PROJ=proj
FILES=syntactic.c scanner.c gramatic_rules.c buffer.c token_buffer.c
CC=gcc
CFLAGS= -g -std=c11 -pedantic -Wall -Wextra
all:syntactic

run:syntactic

$(PROJ) : $(FILES)
		$(CC) -g $(CFLAGS) -o $(PROJ) $(FILES) -lm

clean:
	rm *.o syntactic
