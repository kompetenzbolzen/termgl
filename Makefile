CC		= clang
CPPFLAGS	= -Wall -std=c++11  -fPIC
LDFLAGS		= -shared
SONAME		= termgl

BUILDDIR	= build
SOURCEDIR	= src
OBJECTDIR	= obj
TESTSOURCE	= test
OUTPUT		= lib$(SONAME).so.$(VERSION).$(PATCHLEVEL)

#VERSION
VERSION		= 1
PATCHLEVEL	= 0

SRCS = $(wildcard $(SOURCEDIR)/*.cpp)  
OBJS = $(SRCS:.cpp=.o)
OBJ  = $(OBJS:$(SOURCEDIR)/%=$(OBJECTDIR)/%)

build: dir genversion $(OBJ) 
	@echo [LD] $(OBJ) 
	@$(CC) $(CPPFLAGS) -o $(BUILDDIR)/lib/$(OUTPUT) $(OBJ) $(LDFLAGS) -Wl,-soname=lib$(SONAME).so.$(VERSION)
	@ln -sf $(OUTPUT) $(BUILDDIR)/lib/lib$(SONAME).so.$(VERSION)
	@ln -sf $(OUTPUT) $(BUILDDIR)/lib/lib$(SONAME).so
	@cp $(SOURCEDIR)/c*.h $(BUILDDIR)/inc
	@cp $(SOURCEDIR)/version.h $(BUILDDIR)/inc

dir:
	@mkdir -p $(OBJECTDIR)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/lib
	@mkdir -p $(BUILDDIR)/inc

debug: CFLAGS += -g -D _DEBUG
debug: build;

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	@echo [CC] $<
	@$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJECTDIR)/%.o: example/%.cpp
	@echo [CC] $<
	@$(CC) $(CPPFLAGS) -I$(SOURCEDIR) -c $<

debug: CPPFLAGS+=-g
debug: build

all: clean build

.PHONY: clean doc

clean:
	@echo [ RM ] $(OBJ)
	@echo [ RM ] $(TESTSOURCE).o
	@echo [ RM ] src/version.h
	@echo [ RM ] $(BUILDDIR)/lib $(BUILDDIR)/inc $(BUILDDIR)/test doc/
	@rm -df  $(OBJ) $(TESTSOURCE).o src/version.h
	@rm -Rdf $(BUILDDIR)/lib $(BUILDDIR)/inc $(BUILDDIR)/test doc/

genversion:
	@echo [GEN ] version.h
	@echo "#pragma once" > $(SOURCEDIR)/version.h
	@echo "#define VERSION $(VERSION)" >> $(SOURCEDIR)/version.h
	@echo "#define PATCHLEVEL $(PATCHLEVEL)" >> $(SOURCEDIR)/version.h
	@echo "#define VERSTRING \"`git describe`\"" >> $(SOURCEDIR)/version.h
	@echo "#define DATE \"`date +'%d.%m.20%y'`\"" >> $(SOURCEDIR)/version.h
	@echo "#define TIME \"`date +'%H:%M:%S'`\"" >> $(SOURCEDIR)/version.h
	@echo "#define BUILDER \"`git config user.name`\"" >> $(SOURCEDIR)/version.h
	@echo "#define BUILDERMAIL \"`git config user.email`\"" >> $(SOURCEDIR)/version.h

gentest: debug $(OBJECTDIR)/$(TESTSOURCE).o
	@echo [LD] $(TESTSOURCE).o
	@mkdir -p $(BUILDDIR)/test
	@$(CC) $(CPPFLAGS) -g -o $(BUILDDIR)/test/test $(TESTSOURCE).o $(OBJ) -lstdc++ -lm

run: gentest
	@./$(BUILDDIR)/test/test

memleak: gentest
	@valgrind -v --track-origins=yes "./$(BUILDDIR)/test/test"

doc: genversion
	@mkdir -p doc
	@doxygen .doxygen
