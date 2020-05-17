[![Build Status](https://travis-ci.org/josecelano/c-mandelbrot-arbitrary-precision.svg?branch=master)](https://travis-ci.org/josecelano/c-mandelbrot-arbitrary-precision)

# Mandelbrot in C language with arbitrary precision

This is a proof of concept project. The main goal is do some research in order to allow zooming further than limits of double-precision in the Fractal generation software GNofract4D. More details about the feature on:

* [Official issue for the enhancement](https://github.com/fract4d/gnofract4d/issues/77)
* [Open discussion to define a roadmap for the feature](https://github.com/HyveInnovate/gnofract4d/issues/7)

Detailed explanations about the Mandelbrot Set can be found here:
https://en.wikipedia.org/wiki/Mandelbrot_set

Specific goals for this proof of concept are:

* Test some different C arbitrary precision libraries.
* Performance analysis.
* Try different approaches when arbitrary precision is not needed. How to support both at the same time.

### Math

Basically, there is a mathematical basic Mandelbrot formula (for complex numbers):

```
f(x) = z² + c
```

where `z` and `c` are complex number. 

The Mandelbrot set is the set of complex numbers `c` for which the function does not diverge when iterated from z=0.
Than means, given a `c` complex number, if you apply the formula to that number `n` times using the previous result as the new `z` number, that `c` belongs to Mandelbrot Set if the sequence does not diverge.

You can represent those complex number in a graph where x-axis is the real part of the complex number and y-axis is the imaginary part.

### Drawing the fractal

It draws the portion of the graph between -2 and 2 real and imaginary parts.
Mandelbrot Set is inside those limits.

![Mandelbrot Graph](https://raw.githubusercontent.com/josecelano/c-mandelbrot-arbitrary-precision/master/mandelbrot-graph.png)

## Dev requirements

* Docker version 18.09.7

## Installation

IMPORTANT!: installation is only tested for this Ubuntu version:

```
Distributor ID:	Ubuntu
Description:	Ubuntu 18.04.4 LTS
Release:	18.04
Codename:	bionic
```

Install dependencies:
```
./bin/install_dependencies
```

Install app from source dir (after installing dependencies):
```
./bin/install
```

## Run

Run:
```
./bin/run
```

`run` command will create 2 files in the `output` dir:
* mandelbrot-256x256.ppm (Mandelbrot image)
* mandelbrot-256x256.txt (Mandelbrot ASCII version)
* mandelbrot-iter-256x256.txt (Mandelbrot Iterations Taken Matrix txt version)

You can see those samples files in folder `samples`.

## Development

All commands use docker under the hood.

Setup:
```
./bin/dev_setup
```

Only compile code:
```
./bin/compile
```

Run main program:
```
./bin/dev_run
```

Execute tests:
```
./bin/test
```

Compile and run:
```
./bin/compile && ./bin/dev_run
```

## Related projects

* [Another C Mandelbrot implementation with arbitrary precision](https://github.com/josch/mandelbrot/blob/master/mandel_mpfr.c)
* [PHP Mandelbrot implementation with arbitrary precision](https://github.com/josecelano/php-mandelbrot-arbitrary-precision)

## Performance

Full mandelbrot from (-2,2) to (2,2).

For 256x256px image:
* Size: 256x256px (65536)
* Max iter: 100
* Precision: 32
* Time for matrix generation: 0.452419s = 452419000.000000ns
* Performance: 6.903366e+03‬ ns/px
* Minimum complex x increment: 1.562500e-02 (4/256)
* Minimum complex y increment: 1.562500e-02 (4/256)

For 512x512px image:
* Size: 512x512px (262144)
* Max iter: 100
* Precision: 32
* Time for matrix generation: 1.841765s = 1841765000.000000ns
* Performance: 7.025776e+03‬ ns/px
* Minimum complex x increment: 7.812500e-03 (4/512)
* Minimum complex y increment: 7.812500e-03 (4/512)

For 1024x1024px image:
* Size: 1024x1024px (1048576)
* Max iter: 100
* Precision: 32
* Time for matrix generation: 8.076328s = 8076328000.000000ns
* Performance: 7.702187e+03‬ ns/px
* Minimum complex x increment: 3.906250e-03 (4/1024)
* Minimum complex y increment: 3.906250e-03 (4/1024)

For 8192x8192px image:
* Size: 8192x8192px (67108864)
* Max iter: 100
* Precision: 32
* Time for matrix generation: 444.213337s = 444213337000.000000ns
* Performance: 6.619295e+03‬ ns/px
* Minimum complex x increment: 4.882812e-04 (4/8192)
* Minimum complex y increment: 4.882812e-04 (4/8192)

For 16384x16384px image:
* Size: 16384x16384px (268435456)
* Max iter: 100
* Precision: 32
* Time for matrix generation: 2281.666958s = 2281666958000.000000ns
* Performance: 8.499872e+03‬ ns/px
* Minimum complex x increment: 2.441406e-04 (4/16384)
* Minimum complex y increment: 2.441406e-04 (4/16384)

Performance links:
* [Post with different performance improvement](https://www.martin-ueding.de/posts/mandelbrot-performance/)
* [Another article about Mandelbrot algorithm improvements](https://gist.github.com/mrange/20fa976388167e294aa01a1266ad0a8c)
* [Performance ranking](https://benchmarksgame-team.pages.debian.net/benchmarksgame/performance/mandelbrot.html)
* [List of speed improvements](https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/Mandelbrot_set/mandelbrot#Speed_improvements_-_optimisation)

## Mandelbrot online explorers

This is a list of sites where you can explore Mandelbrot Set:

1. http://mandel.gart.nz/
2. http://math.hws.edu/eck/js/mandelbrot/MB.html
3. https://guciek.github.io/web_mandelbrot.html
4. http://xaos-project.github.io/XaoSjs/
5. https://sciencedemos.org.uk/mandelbrot.php

Some of them let you easily get z real and imaginary values and maximum number of iterations so you can use them with this program to try to reproduce the same result.

## Enhancements

* Do not use arbitrary precision when it's not needed.
* Use a better color map, maybe copy from: https://github.com/josch/mandelbrot/blob/master/mandel_mpfr.c
* Improve performance with "period checking", see also from https://github.com/josch/mandelbrot/blob/master/mandel_mpfr.c

## TODO

* Get `main` arguments from console (resolution and filenames).
* Calculate dynamically needed precision.
* Allow to set a fractal tile and zoom level.
* Function `ztile_set_from_str` should validate tile points (left bottom and right top).

## Debug

How to print arbitrary precision numbers:
```
void console_print_complex(char *prefix, acb_t c);
void console_print_real(char *prefix, arb_t c);
```