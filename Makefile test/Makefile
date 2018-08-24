# Compiler variables, flags
CC = gcc
CFLAGS = -Wall
OFLAGS = -Wall -c

run: executable
	./executable

executable: test_imports.c other_functions.o
	$(CC) $(CFLAGS) test_imports.c other_functions.o -o executable

other_functions.o: other_functions.c
	$(CC) $(OFLAGS) other_functions.c -o other_functions.o

clean:
	rm executable
