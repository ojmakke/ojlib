CC=gcc
CFLAGS=-c -Wall
CDEFS= -DERRLOG -DWARNLOG -DINFOLOG
DEPS = ../ojmemory/ojmemory.o


test: ojllisttest

ojllisttest: main.o 
	$(CC) main.c -o ojlisttest $(DEPS) $(CDEFS)

main.o: main.c
	$(CC) $(CFLAGS) main.c $(CDEFS)

.PHONY: clean

clean: 
	rm -f main.o ojlisttest
