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

### Getting Started (Windows)

We recommend Windows users use Windows Subsystem for Linux (WSL). As of 4/3/2024, we have been unable to _consistently_ get `rpl-sim` working on Windows natively -- and even when we do, there is some odd behavior.

### Getting Started (Unix Variants, Mac, Windows Subsystem for Linux)

#### Install g++
We use g++ as our primary compiler. Others should work, but using `g++` is proven to work.

#### Install CMake 3.22+
We use CMake as a build system. You can either install directly or use a package manager. Be sure to get version 3.22 or greater.

If you use `apt-get`, the default registry has an older version as of 4/3/2024. You should follow the steps in [this AskUbuntu thread](https://askubuntu.com/a/865294).

#### Install and Build Boost
Boost is a large C++ library that `rpl-sim` uses for serial ports, ordinary differential equations, and more. Boost is not embedded inside of `rpl-sim` and must be downloaded separately.

Follow the [instructions on the Boost website](https://www.boost.org/doc/libs/1_84_0/more/getting_started/unix-variants.html) to download the Boost library onto your machine. **We use some libraries that require Boost to be built locally. Be sure to follow the _entire_ guide, particularly section 5.**

We do **not** recommend using a package manager for this dependency.

### Code Style
Follow [Google's C++ style guidelines](https://google.github.io/styleguide/cppguide.html).

## Development using Docker

### Install Docker
* [https://www.docker.com/](https://www.docker.com/)

#### Building Docker Image
```docker build -t rpl-sim .```

#### Running Docker Image
```docker run --rm rpl-sim```

### Expected Test Output
<img src="assets\expected-test-output.png" alt="description" style="width:30%;">

