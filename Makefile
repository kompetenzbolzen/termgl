CC      = /usr/bin/g++
CFLAGS  = -Wall -g -std=c++11
LDFLAGS = -lm -lcurses
OUTPUT = build/Engine

OBJ = main.o cObject.o cObjectHandler.o cRender.o cInput.o

prog: $(OBJ)
	mkdir build
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

all:
	make clean
	make

.PHONY: clean

clean:
	rm -f $(OUTPUT) *.o
	rmdir build
