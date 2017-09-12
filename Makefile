# makefile para prototipo. version 0.1

CC = gcc
TARGETS = atomicTest.c
OBJECTS = atomicTest.o
LIBS = -lOpenCL -lm
CFLAGS = -Ofast -I include


%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)


atomicTest : $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIBS)

all:
	make atomicTest

.PHONY: clean

clean:
	rm -f $(OBJECTS)
