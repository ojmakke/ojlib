CC=gcc
CFLAGS=-c -Wall
CDEFS= -DERRLOG -DWARNLOG -DINFOLOG -DOJ_POSIX_THREAD -DDEBUGLOG
DEPS = ../ojmemory/ojmemory.o
LIBS = pthread

test: ojllisttest

ojllisttest: main.o 
	$(CC) main.c -o ojlisttest $(DEPS) $(CDEFS) -l$(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) main.c $(CDEFS)

.PHONY: clean

clean: 
	rm -f main.o ojlisttest
