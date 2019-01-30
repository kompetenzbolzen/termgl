[![Build Status](https://travis-ci.org/kompetenzbolzen/engine.svg?branch=master)](https://travis-ci.org/kompetenzbolzen/engine)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/9b19f9f7a8d241368f6ee640d824b293)](https://www.codacy.com/app/kompetenzbolzen/engine?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=kompetenzbolzen/engine&amp;utm_campaign=Badge_Grade)

## Compiling

engine should compile just fine with just the c++ standard librarys.
Required Packages:

    g++
    make

this creates two folders in ./build/: lib and inc, wich hold the library and the headers respectively. these can then be copied into your projects directory.

## Using

Compile your program with linkerflags:

    -L./lib -lengine -lstdc++
