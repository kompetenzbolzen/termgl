CC      = /usr/bin/g++
CFLAGS  = -Wall -g -std=c++11
LDFLAGS = -lm -lcurses
<<<<<<< HEAD
OUTPUT = Engine
BUILDDIR = build
=======
OUTPUT = build/Engine
>>>>>>> dfa4ff6eedef580ba562051434cb02582f086c0c

OBJ = main.o cObject.o cObjectHandler.o cRender.o cInput.o

prog: $(OBJ)
<<<<<<< HEAD
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$(OUTPUT) $(OBJ) $(LDFLAGS)
=======
	mkdir build
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJ) $(LDFLAGS)
>>>>>>> dfa4ff6eedef580ba562051434cb02582f086c0c

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

all:
	make clean
	make

.PHONY: clean

clean:
<<<<<<< HEAD
	rm -f $(BUILDDIR)/$(OUTPUT) *.o
	rmdir $(BUILDDIR)
=======
	rm -f $(OUTPUT) *.o
	rmdir build
>>>>>>> dfa4ff6eedef580ba562051434cb02582f086c0c
