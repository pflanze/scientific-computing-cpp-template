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
    TIME(t1, 10) in thread 139804111436800 of pid 1353643:
    =name=	=seconds=
    real	0.113137
    cpu	0.113130
    user	0.111450
    sys	0.001680
    =name=	=count=
    minflt	0	# page reclaims (soft page faults)
    majflt	0	# page faults (hard page faults)
    nswap	0	# swaps
    inblock	0	# block input operations
    oublock	0	# block output operations
    nvcsw	0	# voluntary context switches
    nivcsw	1	# involuntary context switches

    TIME(pot2, 10) in thread 139804111436800 of pid 1353643:
    =name=	=seconds=
    real	0.636802
    cpu	0.636644
    user	0.372706
    sys	0.263939
    =name=	=count=
    minflt	195320	# page reclaims (soft page faults)
    majflt	0	# page faults (hard page faults)
    nswap	0	# swaps
    inblock	0	# block input operations
    oublock	0	# block output operations
    nvcsw	0	# voluntary context switches
    nivcsw	7	# involuntary context switches

    TIME(result = b, 10) in thread 139804111436800 of pid 1353643:
    =name=	=seconds=
    real	0.159072
    cpu	0.159068
    user	0.135328
    sys	0.023743
    =name=	=count=
    minflt	19532	# page reclaims (soft page faults)
    majflt	0	# page faults (hard page faults)
    nswap	0	# swaps
    inblock	0	# block input operations
    oublock	0	# block output operations
    nvcsw	0	# voluntary context switches
    nivcsw	1	# involuntary context switches

    TIME(pot3, 10) in thread 139804111436800 of pid 1353643:
    =name=	=seconds=
    real	0.194419
    cpu	0.194307
    user	0.194310
    sys	0.000000
    =name=	=count=
    minflt	0	# page reclaims (soft page faults)
    majflt	0	# page faults (hard page faults)
    nswap	0	# swaps
    inblock	0	# block input operations
    oublock	0	# block output operations
    nvcsw	0	# voluntary context switches
    nivcsw	3	# involuntary context switches

    TIME(pot3_parallel, 10) in thread 139804111436800 of pid 1353643:
    =name=	=seconds=
    real	0.192760
    cpu	0.190365
    user	0.375401
    sys	0.000000
    =name=	=count=
    minflt	3	# page reclaims (soft page faults)
    majflt	0	# page faults (hard page faults)
    nswap	0	# swaps
    inblock	0	# block input operations
    oublock	0	# block output operations
    nvcsw	4	# voluntary context switches
    nivcsw	25	# involuntary context switches

With parallelism (only `t1` changes via the `parallel` setting):

    $ parallel=1 repetitions=10 ./run 
    n = 10000000
    TIME(t1, 10) in thread 140675027364864 of pid 1353662:
    =name=	=seconds=
    real	0.107637
    cpu	0.107387
    user	0.213387
    sys	0.000000
    =name=	=count=
    minflt	2	# page reclaims (soft page faults)
    majflt	0	# page faults (hard page faults)
    nswap	0	# swaps
    inblock	0	# block input operations
    oublock	0	# block output operations
    nvcsw	0	# voluntary context switches
    nivcsw	8	# involuntary context switches

    ... (omitted)

