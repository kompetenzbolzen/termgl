CC      = /usr/bin/g++
CFLAGS  = -Wall -g
LDFLAGS = -lm -lpthread -lcurses
OUTPUT = Kreuzung

OBJ = main.o cObject.o cObjectHandler.o cRender.o

prog: $(OBJ)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f $(OUTPUT) *.o
