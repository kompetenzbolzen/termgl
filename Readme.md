# TermGL

TermGL is a library for displaying ASCII-graphics in a xterm compatible console (Some parts work in Windows).

List of current features:

- Automatic terminal size detection, online resizing
- Framerate target
- Simple shape-drawing functions
- Object Handling:
	- Movement
	- Collision
- Input handling with object mapping
- 3D wiremeshes (mostly useless eye-candy)

For more information on how to use, consult the documentation (`make doc`) and look at the example programs in `example/`.

## Building from source

TermGL should compile just fine with just `libstdc++`. The Makefile is set up for clang, but gcc should also work.
Required Packages:

    clang
    make

`make` builds the library to `build/lib` and copies all needed header files to `build/inc`

Run `make run` to build and run the example program specified by `$TESTSOURCE` in the Makefile. It is not compiled against the library, but just statically linked with the .o-files for easier debugging. The same example-programs can also be linked with the dynamic library by using the Makefile in `example/`.

To build the documentation, install `doxygen` and run `make doc`.

## Installation

The `makefile` provides a `install` target, which installs headers in `/usr/include/` and the binary in `/usr/lib`. `PREFIX` can be set to alter install location.

PKGBUILD scripts are provided in `packaging` for easy installation on Arch-based systems.
