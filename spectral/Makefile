

CC=gcc
CFLAGS=-Wall -lm

OBJECTS = main.o alloc.o pfafft.o

spectral1d : $(OBJECTS)
	$(CC) -o spectral1d $(OBJECTS)

main.o : cwp.h Complex.h
alloc.o : cwp.h
pfafft.o : cwp.h Complex.h

.PHONY : clean
clean :
	-rm spectral1d $(OBJECTS)


