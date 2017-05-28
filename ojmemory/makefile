CC=gcc
CFLAGS=-c -Wall
CDEFS= -DOJ_POSIX_THREAD -DERRLOG -DWARNLOG -DINFOLOG -DDEBUGLOG -DTESTLOG -DLEVEL1LOG -DLEVEL2LOG -DLEVEL3LOG -DLEVEL4LOG -DLEVEL5LOG
LIBS = pthread


all: actual
test: ojmemorytest

actual: ojmemory.o

ojmemorytest: main.o ojmemory.o
	$(CC) main.c ojmemory.c -o ojmemorytest $(CDEFS) -l$(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) main.c $(CDEFS)

ojmemory.o: ojmemory.c
	$(CC) $(CFLAGS) ojmemory.c

.PHONY: clean

clean: 
	rm -f ojmemory.o main.o ojmemorytest
