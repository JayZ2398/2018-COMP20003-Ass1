CC = gcc
CFLAGS = -Wall

all: run1 run2

run1: dict1
	./dict1 Inputs/athlete_events_filtered.csv Outputs/output1.txt < name_list.txt

run2: dict2
	./dict2 Inputs/athlete_events_filtered.csv Outputs/output2.txt < name_list.txt

dict1: main.c io.c dict1.c
	$(CC) $(CFLAGS) main.c io.c dict1.c -o dict1

dict2: main.c io.c dict2.c
	$(CC) $(CFLAGS) main.c io.c dict2.c -o dict2
