CC=gcc
CFLAGS=-c -Wall
DEPS = ../ojmemory/ojmemory.o
CDEFS= -DERRORLOG -DDEBUGLOG

all: actual


test: strhashtest

actual: ojstrhash.o

strhashtest: main.o ojstrhash.o
	$(CC) $(DEPS) main.c ojhash.c $(CDEFS) -o strhashtest

main.o: main.c
	$(CC) $(CFLAGS) $(CDEFS) main.c

ojstrhash.o: ojhash.c
	$(CC) $(CFLAGS) $(CDEFS) ojhash.c



clean: 
	rm ojstrhash.o main.o strhashtest
