CC = gcc
CFLAGS = -Wall

all: dict1 dict2

dict1: main.c io.c dict1.c
	$(CC) $(CFLAGS) main.c io.c dict1.c -o dict1

dict2: main.c io.c dict2.c
	$(CC) $(CFLAGS) main.c io.c dict2.c -o dict2

clean:
	rm dict1 dict2
