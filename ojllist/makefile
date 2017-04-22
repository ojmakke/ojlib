CC=gcc
CFLAGS=-c -Wall
CDEFS= -DERRLOG -DWARNLOG -DINFOLOG -DDEBUGLOG -DTESTLOG -DLEVEL1LOG -DLEVEL2LOG -DLEVEL3LOG -DLEVEL4LOG -DLEVEL5LOG

test: ojllisttest

ojllisttest: main.o 
	$(CC) main.c -o ojlisttest $(CDEFS)

main.o: main.c
	$(CC) $(CFLAGS) main.c $(CDEFS)

clean: 
	rm main.o ojlisttest
