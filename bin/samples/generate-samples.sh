#!/usr/bin/env bash
# How to use command line

# Tile
LEFT_BOTTOM_ZX=-2.0
LEFT_BOTTOM_ZY=-2.0
TOP_RIGHT_ZX=2.0
TOP_RIGHT_ZY=2.0

# Resolution
RES_X=256
RES_Y=256

# Format
FORMAT_PPM=0
FORMAT_ASCII_GRAPH=1

# Color map
CM_BLACK_ON_WHITE=0
CM_WHITE_ON_BLACK=1
CM_COLORED_PERIODS=2

# ASCII map
AM_AT_SIGN=0
AM_ITERATIONS=1
AM_FULL_ITERATIONS=2
AM_PERIODS=3

# Generate full Mandelbrot image with black on white color map
# ./mandelbrot -prfy -- -2.0 -2.0 2.0 2.0 256 256 0 0
./mandelbrot -- $LEFT_BOTTOM_ZX $LEFT_BOTTOM_ZY \
  $TOP_RIGHT_ZX $TOP_RIGHT_ZY \
  $RES_X $RES_Y \
  $FORMAT_PPM $CM_BLACK_ON_WHITE \
  "./output/mandelbrot-black-on-white-${RES_X}x${RES_Y}.ppm"

# Generate full Mandelbrot text file with @ sign
# ./mandelbrot -prfy -- -2.0 -2.0 2.0 2.0 256 256 0 0
./mandelbrot -- $LEFT_BOTTOM_ZX $LEFT_BOTTOM_ZY \
  $TOP_RIGHT_ZX $TOP_RIGHT_ZY \
  $RES_X $RES_Y \
  $FORMAT_ASCII_GRAPH $AM_AT_SIGN \
  "./output/mandelbrot-at-sign-${RES_X}x${RES_Y}.txt"
