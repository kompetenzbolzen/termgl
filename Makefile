CC      = clang
CFLAGS  = -Wall -g -std=c++11  -fPIC
DEBUGFLAGS = -Wall -g -std=c++11
LDFLAGS = -shared
SONAME = engine
BUILDDIR = build
SOURCEDIR = src
OBJECTDIR = obj
TESTSOURCE = test
#VERSION
VERSION = 0
PATCHLEVEL = 4
OUTPUT = lib$(SONAME).so.$(VERSION).$(PATCHLEVEL)

SRCS=$(wildcard $(SOURCEDIR)/*.cpp)
OBJS =$(SRCS:.cpp=.o)
OBJ =$(OBJS:$(SOURCEDIR)/%=$(OBJECTDIR)/%)

#OBJ = cObject.o cObjectHandler.o cRender.o cInput.o cWiremesh.o

build: dir genversion $(OBJ)
	@echo [LD] $(OBJ)
	@$(CC) $(CFLAGS) -o $(BUILDDIR)/lib/$(OUTPUT) $(OBJ) $(LDFLAGS) -Wl,-soname=lib$(SONAME).so.$(VERSION)
	@ln -sf $(OUTPUT) $(BUILDDIR)/lib/lib$(SONAME).so.$(VERSION)
	@ln -sf $(OUTPUT) $(BUILDDIR)/lib/lib$(SONAME).so
	@cp $(SOURCEDIR)/c*.h $(BUILDDIR)/inc
	@cp $(SOURCEDIR)/version.h $(BUILDDIR)/inc

dir:
	@mkdir -p $(OBJECTDIR)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/lib
	@mkdir -p $(BUILDDIR)/inc


$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	@echo [CC] $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTDIR)/%.o: example/%.cpp
	@echo [CC] $<
	@$(CC) $(CFLAGS) -I$(SOURCEDIR) -c $<


all: clean build

.PHONY: clean doc

clean:
	@echo [RM] $(OBJ)
	@echo [RM] $(TESTSOURCE).o
	@echo [RM] src/version.h
	@echo [RM] $(BUILDDIR)/lib $(BUILDDIR)/inc $(BUILDDIR)/test doc/
	@rm -df  $(OBJ) $(TESTSOURCE).o src/version.h
	@rm -Rdf $(BUILDDIR)/lib $(BUILDDIR)/inc $(BUILDDIR)/test doc/

genversion:
	@echo [GEN] version.h
	@echo "#pragma once" > $(SOURCEDIR)/version.h
	@echo "#define VERSION $(VERSION)" >> $(SOURCEDIR)/version.h
	@echo "#define PATCHLEVEL $(PATCHLEVEL)" >> $(SOURCEDIR)/version.h
	@echo "#define VERSTRING \"`git describe`\"" >> $(SOURCEDIR)/version.h
	@echo "#define DATE \"`date +'%d.%m.20%y'`\"" >> $(SOURCEDIR)/version.h
	@echo "#define TIME \"`date +'%H:%M:%S'`\"" >> $(SOURCEDIR)/version.h
	@echo "#define BUILDER \"`git config user.name`\"" >> $(SOURCEDIR)/version.h
	@echo "#define BUILDERMAIL \"`git config user.email`\"" >> $(SOURCEDIR)/version.h

gentest: build $(OBJECTDIR)/$(TESTSOURCE).o
	@echo [LD] $(TESTSOURCE).o
	@mkdir -p $(BUILDDIR)/test
	@$(CC) $(DEBUGFLAGS) -o $(BUILDDIR)/test/test $(TESTSOURCE).o $(OBJ) -lstdc++ -lm

run: gentest
	@./$(BUILDDIR)/test/test

memleak: gentest
	@valgrind -v --track-origins=yes "./$(BUILDDIR)/test/test"

doc: genversion
	@mkdir -p doc
	@doxygen .doxygen
