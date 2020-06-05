## Fractint web/book

This is only a backup of this page: https://web.archive.org/web/20150220012221/http://www.reocities.com/CapeCanaveral/5003/mandel.htm
It contains information about how Fractint software implemented periodicity checking.

### Mandelbrot Set code

The C programs shown use Allegro for graphics output. Since the only graphical function required is putpixel, it should be trivial to modify the code for other graphics libraries. Qbasic no longer ships with winders, but is available to download from the microsoft webpage. Somewhere... If you can find it.

### Longwinded method

[Speedy Mandelbrot set code](https://web.archive.org/web/20150220012221/http://www.reocities.com/CapeCanaveral/5003/Mandel.txt)

This c function contains a fast implementation of the main loop for the Mandelbrot set calculation. It contains no periodicity checking though, but it compiles very well, and works quickly. The rest of the code required to plot the image is not included.

[Qbasic single pass Mandelbrot set code](https://web.archive.org/web/20150220012221/http://www.reocities.com/CapeCanaveral/5003/qmand.txt)
This complete program draws an unzoomed mandelbrot set image on the screen.

### Integer calculation method

[C integer Mandelbrot set code](https://web.archive.org/web/20150220012221/http://www.reocities.com/CapeCanaveral/5003/cint.txt)

If you don't want to zoom in far, then 32 bit integers are accurate enough. However, the mathematical operations require a little "fiddling", since the numbers are now no longer what they seem to be. This is a good speed up, since integer maths is FAST. However, on pentium processors and above, integer maths emulation of floating point numbers is often slower, since the FPU in the pentium processor is so much better than in 486 types and below.
Fixed point integer maths is easily implemented, and often in assembler, where the necessary multipications and divisions can be performed using bit shifts which are
fast.

This can be a good speed up on some types of hardware, since integer maths can be much faster than standard floating point maths. Unfortunately though, the Mandelbrot set likes floating point numbers, and accurate ones at that too! The problem is representing non integers by an integer. Below is an illustration of how we would do a non integer sum:

0.0123 * 1.246 = A First we multiply both numbers by 10000

1234 * 12460 = X Notice now how all the numbers are integers

X = 15375640 This is not the correct answer yet though

A = X / 10000² i.e. A = 0.1537564

Which is the answer to the above sum. Integer fractal programs work in the same way. The above C program multiplies by 2^25 (33554432). This makes it accurate to 2.98 * 10 ^-8 (i.e. about 8 dp). Powers of two are much better for computers, since they can multiply or divide by them using logical bit shifts (>> and << in C) very quickly. This process is the fixed point method of storing non integer numbers. Addition and subtraction require no bit shifting. That is exactly how the above program works.

The "function" fixpt(a) converts a fixed point number to a long integer, mul (a,b) returns the product of a and b (both large integers) and rescales the answer. Integer (a) converts a long integer number into a small fixed point number. (not needed in my program). Notice how the program is identical to the other singlepass C program, but over twice as fast! FIXSIZE is the "fudge factor" (represents 2^25). If is is made bigger, then the program malfunctions, since some numbers suddenly become negative for no apparent reason! (Actually because the sign bit in the 2s complement representation becomes altered by bit shifting.) Making it smaller makes the numbers more inaccurate.

### Boundary tracing method

[Qbasic boundary tracing code](https://web.archive.org/web/20150220012221/http://www.reocities.com/CapeCanaveral/5003/qbound.txt)

It can be shown that if a solid shape can be drawn on the mandelbrot set, with all the border colours being the same, then the shape can be filled in with that colour. This is a result of the Mandelbrot set being simply connected. A description of this can be found sci.fractals faq. Boundary tracing works by following the edges of the various iteration levels (coloured bands) all around, then filling the shape in. This can be a good speed up, because it means that large numbers of points can be skipped. My boundary tracing program is not very good, but it works. It has to work out the whole set.
This program is not really mine, but was modified out of a dubious book ages ago. Take it or leave it!

The program starts by at iteration -2, and works up, drawing the boundary, then filling in from the middle. A slow way of doing it, but it works.
PS program is not properly documented play with at your peril!!

[Qbasic Teressal code](https://web.archive.org/web/20150220012221/http://www.reocities.com/CapeCanaveral/5003/qteres.txt)

[C Teressal fractal program](https://web.archive.org/web/20150220012221/http://www.reocities.com/CapeCanaveral/5003/cteres.txt) - written by David Chan (dpchan@kentroad.demon.co.uk)
This is a bit like boundary tracing (same principle), except it uses rectangles instead of the actual wiggly boundary. It is usually faster than boundary tracing because it requires fewer calculations to work out the rectangle. It is inefficient however because the boundaries are not rectangular, and so bits get missed out. It can be improved my using a recursive algorithm which selects the most appropriate (largest) sized rectangle. My teressal algorithm is described if you follow the link.

*May need QuickBasic in order to use upper memory for storing the whole screen in integer array. (STUPID!))

There are a few speedups in this program which is why it is so messy. QuickBasic function calls are SLOW. Hence the use of 2 identical mandelbrot subroutines. Also the subroutine stores the colour of each point in the big array, because some points may be recalculated, and it's quicker to look them up than recalculate them. This bit can be omitted, but will slow the program down.

How it works

Start off with the full screen. Have a sub which accepts the co-ordinates of the corners of the screen. This sub then divides the screen into 4 quarters. Next, the function checks the colours all around the edges of each of the 4 rectangles, by working out those particular points using the standard 1 pass algorithm (the subroutine mand in the program). If the colours all around a rectangle are ALL the same, then that rectangle is filled in with that colour. This is repeated for all the 4 rectangles. If the colours around a particular rectangle are not all identical, then the sub calls itself (recurses), and repeats the whole divide procedure for that one rectangle. If a rectangle is smaller than 2*2 then it is worked out fully. This procedure is repeated for all the rectangles. When all 4 rectangles have been filled in, the sub exits. Eventually the screen is completely drawn, and the program ends.

### Periodicity Checking
Sorry, no sample programs! This section is taken from Fractint book, written by the authors of Fractint.

Periodicity checking is a small check which is done every iteration to see if Z becomes periodic. If Z becomes periodic, then there is no point carrying on with the iteration, since it represents a point which MUST be inside the M set. Sample code:

Initialisation routine

aX=0, aY=0

Period=1

Check=3

Checking routine (x & y are the values x0² - y0² + p and 2x0y0 + q resp)

if x = aX AND y = aY then PeriodicityFlag = 1: Exit procedure Quit if periodic

Else

Period=Period + 1

if Period > Check then Check=Check*2 : Period=1 : aX=x : aY=y

PeriodicityFlag=0

Exit procedure

Notice how Check is continuously increased, this is so that larger periods are not missed.

The algorithm is quite slow, but there are a lot of iterations (e.g. 1000) and the middle of the lake is being checked, then there is a HUGE speedup. However it is a good idea if the periodicity checking is only done if the last point computed was inside the mandelbrot set. This is what fractint does, and it stops time being wasted on points which obviously are not periodic.

If the line which checks if x=aX and y=aY is replaced with x~aX and y~aY then the program can be sped up even more. However, this may now falsely detect points which are not periodic.

Note all these programs are old, and so are not commented. Sorry. Where necessary I have explained how they work in this doc

General notes:
* Consider obtaining Microsoft QuickBasic, it uses the coprocessor, and is about 10 times faster than Qbasic - more on a really good PC ;). Also it allows compiling programs which makes them even faster.
* For all real mode software (i.e. QuickBasic etc. but NOT DJGPP), boot your computer bare, or avoid emm386. This nasty program SLOWS DOWN THE COMPUTER, and these programs can go 2-3 times faster without it!
* Don't run DOS programs from Windows (ANY Windows)
* Don't send me emails telling me how unreadable my programs are. I know!!!!!