CC=gcc
CFLAGS=-c -Wall
CDEFS= -DERRLOG -DWARNLOG -DINFOLOG -DDEBUGLOG -DTESTLOG -DLEVEL1LOG -DLEVEL2LOG -DLEVEL3LOG -DLEVEL4LOG -DLEVEL5LOG

all: actual
test: ojmemorytest

actual: ojmemory.o

ojmemorytest: main.o ojmemory.o
	$(CC) main.c ojmemory.c -o ojmemorytest $(CDEFS)

main.o: main.c
	$(CC) $(CFLAGS) main.c $(CDEFS)

ojmemory.o: ojmemory.c
	$(CC) $(CFLAGS) ojmemory.c


clean: 
	rm ojmemory.o main.o ojmemorytest
