CC=gcc
CFLAGS=-c -Wall
DEPS = ../ojmemory/ojmemory.o
CDEFS= -DERRORLOG -DDEBUGLOG -DTESTLOG -DINFOLOG

all: actual

test: strhashtest

actual: ojstrhash.o

strhashtest: main.o ojstrhash.o
	$(CC) $(DEPS) main.c ojhash.c $(CDEFS) -o strhashtest

main.o: main.c
	$(CC) $(CFLAGS) $(CDEFS) main.c

ojstrhash.o: ojhash.c
	$(CC) $(CFLAGS) $(CDEFS) ojhash.c


.PHONY: clean

clean: 
	rm -f ojstrhash.o main.o strhashtest
