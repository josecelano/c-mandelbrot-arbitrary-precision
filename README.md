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

## Install

>IMPORTANT: Not tested yet. It's just a copy&paste from Dockerfile.

```
./install
```

## Development commands

All commands use docker under the hood.

Setup:
```
./dev_setup
```

Only compile code:
```
./compile
```

Run main program (it generates a ppm image and txt file with Mandelbrot fractal):
```
./run
```

Execute tests:
```
./test
```

Compile and run:
```
./compile && ./run
```

## Related projects

* [Another C Mandelbrot implementation with arbitrary precision](https://github.com/josch/mandelbrot/blob/master/mandel_mpfr.c)
* [PHP Mandelbrot implementation with arbitrary precision](https://github.com/josecelano/php-mandelbrot-arbitrary-precision)

## Performance

For 8192px image:
* Size: 8192x8192px
* Iter: 200
* Precision: 32
* Time: 30m
* Performance: 26822,09014892578125 ns/px
* Min number step: 0,00048828125 (4/8192)

## TODO

* Get `main` arguments from console (resolution and filenames).
* Calculate dynamically needed precision.
* Allow to set a fractal tile and zoom level.
* Refactor fractal::calculate_points function.