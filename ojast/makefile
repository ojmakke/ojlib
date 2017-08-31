CC=gcc 
CFLAGS=-c -Wall 
DEPS = ../ojmemory/ojmemory.o 
CDEFS= -DERRLOG -DDEBUGLOG -DTESTLOG -DINFOLOG

all: actual

test: ojasttest

actual: ojast.o

ojasttest: main.o ojast.o
	$(CC) $(DEPS) main.c ojast.c $(CDEFS) -o ojasttest

main.o: main.c
	$(CC) $(CFLAGS) $(CDEFS) main.c

ojast.o: ojast.c
	$(CC) $(CFLAGS) $(CDEFS) ojast.c


.PHONY: clean

clean: 
	rm -f ojast.o main.o ojasttest
