# cstring_view

## Overview

A library that is very similar to C++17 std::string_view, but written in C. All functions are

## Building Tests and Examples
```bash
mkdir build
cd build
cmake ..
make
```

## Running Tests
Building from previous step will generate two directories, tests and examples. This is where the binaries are stored. Running the examples is as simple as running each outputted binary from the command line. You can easily run the tests with the `make` or `ctest` command like so:
```bash
make test                 # or
ctest --output-on-failure
```


## Examples
Look in the [examples/](examples) directory.

