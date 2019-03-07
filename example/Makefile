CC     = /usr/bin/g++
CFLAGS  = -Wall -g -std=c++11
LIBDIR = ../build/lib
INCDIR = ../build/inc

%: %.cpp
	$(CC) -I$(INCDIR) -L$(LIBDIR) $(CFLAGS) -lengine $< -o $@.out
	LD_LIBRARY_PATH=$(LIBDIR) ./$@.out

.PHONY: clean

clean:
	rm -df *.out
