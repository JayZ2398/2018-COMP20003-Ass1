CC = gcc
CFLAGS = -Wall
OFLAGS = -Wall -g

all: dict1 dict2

test: dict1 dict2
	cp dict1 dict2 Testing/

debug:
	$(CC) $(OFLAGS) main.c io.c dict1.c -o dict1
	$(CC) $(OFLAGS) main.c io.c dict2.c -o dict2

dict1: main.c io.c dict1.c
	$(CC) $(CFLAGS) main.c io.c dict1.c -o dict1

dict2: main.c io.c dict2.c
	$(CC) $(CFLAGS) main.c io.c dict2.c -o dict2

clean:
	rm dict1 dict2
