# cstring_view

## Overview

A header only library that is very similar to C++17 std::string_view, but written in C.

## Building Tests and Examples
```bash
mkdir build
cd build
cmake ..
make
```

## Running Tests and Examples
Building from previous step will generate two directories, tests and examples. This is where the binaries are stored. Running the examples is as simple as running each outputted binary from the command line. You can easily run the tests with `ctest` command like so:
```bash
ctest --output-on-failure
```

The tests can be found in the [tests](tests) directory and the examples can be found in the [examples](examples) directory.

## Including this library in your project
The library is header only, so you can easily add it to your project. Copy and paste [sv.h](sv.h) into your project. You must also do:

```c++
   // Do this:
      #define STB_IMAGE_IMPLEMENTATION
   // before you include this file in *one* C or C++ file to create the implementation.
   
   // i.e. it should look like this:
   #include ...
   #include ...
   #include ...
   #define SV_IMPLEMENTATION
   #include "sv.h"
```

