CC = gcc
CFLAGS = -Wall
OFLAGS = -Wall -c

all: run

run: dict1
	./dict1 Inputs/athlete_events_filtered.csv output.txt < name_list.txt

dict1: dict1.c bst.o
	$(CC) $(CFLAGS) dict1.c bst.o -o dict1

bst.o: bst.c
	$(CC) $(OFLAGS) bst.c -o bst.o

clean:
	rm *.o
