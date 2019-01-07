CC      = /usr/bin/g++
CFLAGS  = -Wall -g -std=c++11
LDFLAGS = -lm -lcurses
OUTPUT = Engine
BUILDDIR = build

OBJ = main.o cObject.o cObjectHandler.o cRender.o cInput.o

debug: $(OBJ)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$(OUTPUT) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

all: clean debug

.PHONY: clean

clean:
	rm -f $(BUILDDIR)/$(OUTPUT) *.o
	rmdir --ignore-fail $(BUILDDIR)
