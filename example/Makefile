CC     = /usr/bin/g++
LIBDIR = ../build/lib
INCDIR = ../build/inc

.PHONY: pong

pong:
	$(CC) -I$(INCDIR) -L$(LIBDIR) -lengine $@.cpp -o $@.out
	LD_LIBRARY_PATH=$(LIBDIR) ./$@.out
