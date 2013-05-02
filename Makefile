# makefile for onedfd

CC=gcc
CFLAGS=-Wall -lm

EXECUTABLE=onedfd
CODE=eindfd.c
OUTFILE=test


all: $(EXECUTABLE)

$(EXECUTABLE): $(CODE)
	$(CC) $(CFLAGS) $(CODE) -o $(EXECUTABLE)


clean:
	rm -rf *.o $(EXECUTABLE) $(OUTFILE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

show:
	suaddhead < $(OUTFILE) ns=100 | suflip flip=0| suximage
