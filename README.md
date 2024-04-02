# rpl-sim

## Using `rpl-sim`

### Error Codes

- `0`: Success
- `1`: Missing required command line argument.
- `2`: Help command was received; displayed help instead of running.
- `3`: A file had a parsing error. Check your JSON.

- `3`: No serial port for flight computer provided, or did not explicitly use `--no-device` option to denote no explicit device.
- `4`: Output File Path Invalid
- `5`: Input File Could Not Be Opened

## Developing `rpl-sim`



### Getting Started (Unix Variants, Windows Subsystem for Linux)

We recommend Windows users use Windows Subsystem for Linux (WSL).

#### Install g++
We use g++ as our primary compiler. Others should work, but using `g++` is proven to work.

#### Install CMake
We use CMake as a build system.

#### Install Boost
Boost is a large C++ library that `rpl-sim` uses for serial ports, ordinary differential equations, and more. Boost is not embedded inside of `rpl-sim` and must be downloaded separately.

Follow the [instructions on the Boost website](https://www.boost.org/doc/libs/1_84_0/more/getting_started/unix-variants.html) to download the Boost library onto your machine.

### Getting Started (Windows)

#### Install Makefile for Windows


### Building the Project
Run `make` 

### Code Style
Follow [Google's C++ style guidelines](https://google.github.io/styleguide/cppguide.html).