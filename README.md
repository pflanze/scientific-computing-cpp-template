# Scientific computing C++ template
 
Skeleton in C++ to experiment with for simple scientific computing.

This currently only works on POSIXy systems, because of the number
parsing and timing libraries.

Run `./run`, it will compile and run the executable. Compilation takes
the following environment variables:

  * `OPTIM`: optimization flags (`-O2` by default)
  * `CPP`: the C compiler (`g++` by default)
  * `USE_SAN`: if set, runs under the sanitizers
  * for others, see `run`

Runtime settings are also taken from environment variables:

  * `parallel`: if set to `1`, parallelisation via
    [OpenMP](https://en.wikipedia.org/wiki/OpenMP) is activated
  * `n`: the number of iterations to run (default: 1)
  * `repetitions`: how many times benchmarks (via `time_this`) should
    be repeated (default: 1)

E.g. without parallelism

    $ repetitions=10 ./run 
    n = 10000000
    TIME(t1, 10) in thread 140034841652224 of pid 1347249:
    =name=	=seconds=
    real	0.117471
    cpu	0.117377
    user	0.116214
    sys	0.001164
    =name=	=count=
    minflt	0	# page reclaims (soft page faults)
    majflt	0	# page faults (hard page faults)
    nswap	0	# swaps
    inblock	0	# block input operations
    oublock	0	# block output operations
    nvcsw	0	# voluntary context switches
    nivcsw	2	# involuntary context switches

    TIME(t2, 10) in thread 140034841652224 of pid 1347249:
    =name=	=seconds=
    real	0.686554
    cpu	0.686253
    user	0.422914
    sys	0.263340
    =name=	=count=
    minflt	195320	# page reclaims (soft page faults)
    majflt	0	# page faults (hard page faults)
    nswap	0	# swaps
    inblock	0	# block input operations
    oublock	0	# block output operations
    nvcsw	0	# voluntary context switches
    nivcsw	5	# involuntary context switches

With parallelism (only `t1` changes via the `parallel` setting):

    $ parallel=1 repetitions=10 ./run 
    n = 10000000
    TIME(t1, 10) in thread 139894343400448 of pid 1347261:
    =name=	=seconds=
    real	0.286388
    cpu	0.285097
    user	0.566525
    sys	0.000000
    =name=	=count=
    minflt	2	# page reclaims (soft page faults)
    majflt	0	# page faults (hard page faults)
    nswap	0	# swaps
    inblock	0	# block input operations
    oublock	0	# block output operations
    nvcsw	0	# voluntary context switches
    nivcsw	38	# involuntary context switches

    TIME(t2, 10) in thread 139894343400448 of pid 1347261:
    =name=	=seconds=
    real	0.690171
    cpu	0.689655
    user	0.452491
    sys	0.238824
    =name=	=count=
    minflt	195320	# page reclaims (soft page faults)
    majflt	0	# page faults (hard page faults)
    nswap	0	# swaps
    inblock	0	# block input operations
    oublock	0	# block output operations
    nvcsw	1	# voluntary context switches
    nivcsw	10	# involuntary context switches

