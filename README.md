[![Build Status](https://travis-ci.org/josecelano/c-mandelbrot-arbitrary-precision.svg?branch=master)](https://travis-ci.org/josecelano/c-mandelbrot-arbitrary-precision)

# Mandelbrot in C language with arbitrary precision

This is a proof of concept project. The main goal is do some research in order to allow zooming further than limits of double-precision in the Fractal generation software [Gnofract 4D](https://github.com/fract4d/gnofract4d). More details about the feature on:

* [Official issue for the enhancement](https://github.com/fract4d/gnofract4d/issues/77)
* [Open discussion to define a roadmap for the feature](https://github.com/HyveInnovate/gnofract4d/issues/7)

Specific goals for this proof of concept are:

* Implement and generate documentation for some techniques used by the software like period checking.
* Performance analysis.
* Try different approaches when arbitrary precision is not needed. How to support both at the same time.
* Test some different C arbitrary precision libraries.

## Installation

Install dependencies:
```
./bin/install_dependencies
```

Install app from source dir (after installing dependencies):
```
./bin/install
```

>IMPORTANT!: installation is only tested for this Ubuntu version:

```
Distributor ID:	Ubuntu
Description:	Ubuntu 18.04.4 LTS
Release:	18.04
Codename:	bionic
```

## Run

Help:
```
./mandelbrot --help
```
You will see the list of options and arguments. And, for example, if you want to generate the full Mandelbrot Set in PPM format with color map "black on white":
```
./mandelbrot -prfy -- -2.0 -2.0 2.0 2.0 256 256 0 0
```
It generates a file in `output` folder with this name: `mandelbrot-black-on-white-256x256.ppm`

Generate samples:
```
./bin/samples/generate-all-samples.sh
```
This command generates one sample file in `output` folder for each color and ascii map available. 

See more command samples in [here](bin/samples/generate-samples.sh).

## Development

Requirements:
* Docker version 18.09.7

All commands use docker under the hood.

Setup:
```
./bin/dev-setup
```

Execute tests:
```
./bin/test
```

Compile and run:
```
./bin/compile && ./bin/dev-run
```

## Documentation

- [Mandelbrot Set](doc/mandelbrot_set.md)
- [Optimisation](doc/optimisation.md)
  * [Main cardioid detection](doc/main-cardioid-detection.md)
  * [Period detection](doc/period2-detection.md)
  * [Periodicity checking](doc/periodicity-checking.md)  
- [Performance](doc/performace.md)
- [Links](doc/links.md)