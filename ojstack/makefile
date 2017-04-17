CC=gcc
CFLAGS=-c -Wall

all: actual


test: stacktest

actual: ojstack.o

stacktest: main.o ojstack.o
	$(CC) main.c ojstack.c -o stacktest

main.o: main.c
	$(CC) $(CFLAGS) main.c

ojstack.o: ojstack.c
	$(CC) $(CFLAGS) ojstack.c


clean: 
	rm ojstack.o main.o stacktest
