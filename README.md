# piping-hot-images

## Overview

A library that reads and writes PNM image files. It supports PBM, PGM, and PPM, for both plain and binary file formats.

## Building Tests and Examples
```bash
mkdir build
cd build
cmake ..
make

```

## Running Tests and Examples
Building from previous step will generate two directories, tests and examples. This is where the binaries are stored. Running the examples is as simple as running each outputted binary from the command line. You can easily run the tests with the `make` or `ctest` command like so:
```bash
make test                 # or
ctest --output-on-failure
```


## Examples
Look in the [examples/](examples) directory. It shows how to read from an PNM image, static/dynamic image allocation, and some conversions fron one PNM format to the other.

## How to view your generated images
The only viewer that I know of that can view PNM images and comes pre-installed with Ubuntu 20.04.5 LTS is the GNOME Image Viewer, or Eye of GNOME. You can easily open your generated PNM with the 'eog' command line tool.
```bash
eog /PATH/TO/FILE
```

## TODO
- Give a good name
- Add a license
- Add that is can be a general purposed 2d array
- Add how to include in project
- Add how to convert to more sensible image, like PNG
- Set up sanitizer# cstring_view
