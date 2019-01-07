CC      = /usr/bin/g++
CFLAGS  = -Wall -g -std=c++11
LDFLAGS = -lm -lcurses
OUTPUT = Engine
BUILDDIR = build

OBJ = main.o cObject.o cObjectHandler.o cRender.o cInput.o

prog: $(OBJ)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$(OUTPUT) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

all:
	make clean
	make

.PHONY: clean

clean:
	rm -f $(BUILDDIR)/$(OUTPUT) *.o
	rmdir $(BUILDDIR)
