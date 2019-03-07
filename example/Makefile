CC     = clang
CFLAGS  = -Wall -g -std=c++11 -lstdc++
LIBDIR = ../build/lib
INCDIR = ../build/inc

%: %.cpp
	$(CC) -I$(INCDIR) -L$(LIBDIR) $(CFLAGS) -lengine $< -o $@.out
	LD_LIBRARY_PATH=$(LIBDIR) ./$@.out

.PHONY: clean

clean:
	rm -df *.out
