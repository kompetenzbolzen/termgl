[![Build Status](https://travis-ci.org/kompetenzbolzen/engine.svg?branch=master)](https://travis-ci.org/kompetenzbolzen/engine)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/9b19f9f7a8d241368f6ee640d824b293)](https://www.codacy.com/app/kompetenzbolzen/engine?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=kompetenzbolzen/engine&amp;utm_campaign=Badge_Grade)

# engine (the most creative name I could come up with)

engine is a library for displaying ASCII-graphics in a text console. For more information on how to use, consult the documentation (`make doc`) and look at the example program in `test.cpp`.

## Compiling the library

engine should compile just fine with just the c++ standard librarys.
Required Packages:

    g++
    make

`make` creates two folders in ./build/: lib and inc, wich hold the library and the headers respectively. these can then be copied into your projects directory. Run `make run` to build and run the example program.

To build the documentation, install `doxygen` and run `make doc`.

## Compile your project

Compile your program with linkerflags:

    -L/path/to/lib -lengine -lstdc++
