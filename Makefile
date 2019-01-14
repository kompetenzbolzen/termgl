CC      = /usr/bin/g++
CFLAGS  = -Wall -g -std=c++11 -Werror=missing-prototypes
LDFLAGS =
OUTPUT = Engine
BUILDDIR = build
#VERSION
VERSION = 0
PATCHLEVEL = 1

OBJ = main.o cObject.o cObjectHandler.o cRender.o cInput.o cWiremesh.o

debug: genversion $(OBJ)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$(OUTPUT) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	@echo
	@echo Building $<
	@echo ==============
	@echo
	$(CC) $(CFLAGS) -c $<

all: clean debug

.PHONY: clean

clean:
	rm -df $(BUILDDIR)/$(OUTPUT) *.o version.h

run: debug
	./$(BUILDDIR)/$(OUTPUT)

genversion:
	@echo Building Version
	@echo "//Generated my MAKEFILE. DO NOT Edit." > version.h
	@echo "#pragma once" >> version.h
	@echo "#define VERSION $(VERSION)" >> version.h
	@echo "#define PATCHLEVEL $(PATCHLEVEL)" >> version.h
	@echo "#define BRANCH \"`git status -bs | grep '##'`\"" >> version.h
	@echo "#define DATE \"`date +'%d.%m.20%y'`\"" >> version.h
	@echo "#define TIME \"`date +'%H:%M:%S'`\"" >> version.h
