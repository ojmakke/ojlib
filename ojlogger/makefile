CC=gcc
CFLAGS=-c -Wall 
CDEFS= -DERRLOG -DWARNLOG -DINFOLOG -DDEBUGLOG -DLEVEL1LOG -DLEVEL2LOG -DLEVEL3LOG -DLEVEL4LOG -DLEVEL5LOG

#all: actual

test: ojloggertest

#actual: ojlogger.o

ojloggertest: main.o
	$(CC) main.c -o ojloggertest $(CDEFS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean: 
	rm main.o ojloggertest
