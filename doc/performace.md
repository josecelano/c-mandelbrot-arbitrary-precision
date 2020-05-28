## Performance

### Tests

Full mandelbrot from (-2,2) to (2,2).

For 256x256px image:
* Size: 256x256px (65536)
* Max iter: 100
* Precision: 32
* Time for matrix generation: 0.801859s = 801859000.000000ns
* Performance: 1.223540e+04‬ ns/px
* Minimum complex x increment: 1.562500e-02 (4/256)
* Minimum complex y increment: 1.562500e-02 (4/256)
* Number of found periods: 5610
* Max for number of iterations: 100 (should be max iterations in config)

For 512x512px image:
* Size: 512x512px (262144)
* Max iter: 100
* Precision: 32
* Time for matrix generation: 3.385562s = 3385562000.000000ns
* Performance: 1.291489e+04‬ ns/px
* Minimum complex x increment: 7.812500e-03 (4/512)
* Minimum complex y increment: 7.812500e-03 (4/512)
* Number of found periods: 22496
* Max for number of iterations: 100 (should be max iterations in config)

For 1024x1024px image:
* Size: 1024x1024px (1048576)
* Max iter: 100
* Precision: 32
* Time for matrix generation: 14.065436s = 14065436000.000000ns
* Performance: 1.341385e+04‬ ns/px
* Minimum complex x increment: 3.906250e-03 (4/1024)
* Minimum complex y increment: 3.906250e-03 (4/1024)
* Number of found periods: 90046
* Max for number of iterations: 100 (should be max iterations in config)

For 4096x4096px image:
* Size: 4096x4096px (16777216)
* Max iter: 100
* Precision: 32
* Time for matrix generation: 203.359067s = 203359067000.000000ns
* Performance: 1.212114e+04‬ ns/px
* Minimum complex x increment: 9.765625e-04 (4/4096)
* Minimum complex y increment: 9.765625e-04 (4/4096)
* Number of found periods: 1441140
* Max for number of iterations: 100 (should be max iterations in config)

For 8192x8192px image:
* Size: 8192x8192px (67108864)
* Max iter: 100
* Precision: 32
* Time for matrix generation: 795.066716s = 795066716000.000000ns
* Performance: 1.184742e+04‬ ns/px
* Minimum complex x increment: 4.882812e-04 (4/8192)
* Minimum complex y increment: 4.882812e-04 (4/8192)
* Number of found periods: 5764706
* Max for number of iterations: 100 (should be max iterations in config)

For 16384x16384px image:
* Size: 16384x16384px (268435456)
* Max iter: 100
* Precision: 32
* Time for matrix generation: 2281.666958s = 2281666958000.000000ns
* Performance: 8.499872e+03‬ ns/px
* Minimum complex x increment: 2.441406e-04 (4/16384)
* Minimum complex y increment: 2.441406e-04 (4/16384)

### Links

* [Post with different performance improvements](https://www.martin-ueding.de/posts/mandelbrot-performance/)
* [Another article about Mandelbrot algorithm improvements](https://gist.github.com/mrange/20fa976388167e294aa01a1266ad0a8c)
* [Performance ranking](https://benchmarksgame-team.pages.debian.net/benchmarksgame/performance/mandelbrot.html)
* [List of speed improvements](https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/Mandelbrot_set/mandelbrot#Speed_improvements_-_optimisation)
