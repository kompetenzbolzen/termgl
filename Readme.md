[![Build Status](https://travis-ci.org/kompetenzbolzen/engine.svg?branch=master)](https://travis-ci.org/kompetenzbolzen/engine)

# Compiling

engine should compile just fine with just the c++ standard librarys.
Required Packages:

  g++
  make

this creates two folders in ./build/: lib and inc, wich hold the library and the headers respectively. these can then be copied into your projects directory.

# Using

Compile your program with linkerflags:

  -L./lib -lengine -lstdc++
