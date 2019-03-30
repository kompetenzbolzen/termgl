[![Build Status](https://travis-ci.org/kompetenzbolzen/TermGL.svg?branch=master)](https://travis-ci.org/kompetenzbolzen/TermGL)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/9b19f9f7a8d241368f6ee640d824b293)](https://www.codacy.com/app/kompetenzbolzen/TermGL?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=kompetenzbolzen/TermGL&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/kompetenzbolzen/TermGL/badge/master)](https://www.codefactor.io/repository/github/kompetenzbolzen/TermGL/overview/master)

# TermGL

TermGL is a library for displaying ASCII-graphics in a xterm compatible console (Some parts work in Windows).

List of current features:

 - Automatic terminal size detection, online resizing
 - Framerate target
 - Simple drawing functions
 - Object Handling:
    - Movement
    - Collision
 - Input handling with object mapping
 - 3D wiremeshes (mostly useless eye-candy)

For more information on how to use, consult the documentation (`make doc`) and look at the example programs in `example/`.

## Compiling the library

TermGL should compile just fine with just the c++ standard librarys. The Makefile is set up for clang, but gcc should also work.
Required Packages:

    clang
    make

`make` creates two folders in `build/`: lib and inc, wich hold the library and the headers respectively. these can then be copied into your projects directory.

Run `make run` to build and run the example program specified by `$TESTSOURCE` in the Makefile. It is not compiled against the library, but just statically linked with the .o-files for easier debugging. The same example-programs can also be linked with the dynamic library by using the Makefile in `example/`.

To build the documentation, install `doxygen` and run `make doc`.

## Compile your project

Compile your program with linkerflags:

    -L/path/to/lib -ltermgl -lstdc++
