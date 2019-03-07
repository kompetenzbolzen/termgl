CC     = /usr/bin/g++
LIBDIR = ../build/lib
INCDIR = ../build/inc

%: %.cpp
	$(CC) -I$(INCDIR) -L$(LIBDIR) -lengine $< -o $@.out
	LD_LIBRARY_PATH=$(LIBDIR) ./$@.out

.PHONY: clean

clean:
	rm -df *.out
