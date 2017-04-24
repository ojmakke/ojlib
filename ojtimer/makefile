CC=gcc
CFLAGS=-c -Wall

all: actual


test: timertest

actual: ojtimer.o

timertest: main.o ojtimer.o
	$(CC) main.c ojtimer.c -o timertest -lrt

main.o: main.c
	$(CC) $(CFLAGS) main.c

ojtimer.o: ojtimer.c
	$(CC) $(CFLAGS) ojtimer.c

.PHONY: clean

clean: 
	rm -f ojtimer.o main.o timertest
