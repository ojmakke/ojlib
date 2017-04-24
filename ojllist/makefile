CC=gcc
CFLAGS=-c -Wall
CDEFS= -DERRLOG -DWARNLOG -DINFOLOG

test: ojllisttest

ojllisttest: main.o 
	$(CC) main.c -o ojlisttest $(CDEFS)

main.o: main.c
	$(CC) $(CFLAGS) main.c $(CDEFS)

.PHONY: clean

clean: 
	rm -f main.o ojlisttest
