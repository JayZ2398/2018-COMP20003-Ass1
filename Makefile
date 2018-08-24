CC = gcc
CFLAGS = -Wall
OFLAGS = -Wall -c

dict1: dict1.c bst.o
	$(CC) $(CFLAGS) dict1.c bst.o -o dict1

bst.o: bst.c
	$(CC) $(OFLAGS) bst.c -o bst.o
