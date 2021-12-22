/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <cstdio>

#include "err.hpp"

#include "time.hpp"

struct Timestamp get_timestamp() {
    struct Timestamp t;
    if (clock_gettime(CLOCK_MONOTONIC, &t.real)<0)
        throwWithStrerror("clock_gettime(CLOCK_MONOTONIC)");
    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t.cpu)<0)
        throwWithStrerror("clock_gettime(CLOCK_THREAD_CPUTIME_ID)");
    if (getrusage(RUSAGE_SELF, &t.rusage) < 0)
        throwWithStrerror("getrusage(RUSAGE_SELF)");
    return t;
}

static double timeval_diff(const struct timeval &start,
                           const struct timeval &end) {
    return ((double)(end.tv_sec - start.tv_sec)
            + (double)(end.tv_usec - start.tv_usec) / 1e6);
}

static double timespec_diff(const struct timespec &start,
                            const struct timespec &end) {
    return ((double)(end.tv_sec - start.tv_sec)
            + (double)(end.tv_nsec - start.tv_nsec) / 1e9);
}

void time_print(const char *expr,
                struct Timestamp &start,
                struct Timestamp &end,
                int n) {
    fprintf(stderr,
            "TIME(%s, %i) in thread %li of pid %i:\n"
            "=name=\t=seconds=\n"
            "real\t%f\n"
            "cpu\t%f\n"
            "user\t%f\n"
            "sys\t%f\n"
            "=name=\t=count=\n"
            "%s\t%li\t# %s\n"
            "%s\t%li\t# %s\n"
            "%s\t%li\t# %s\n"
            "%s\t%li\t# %s\n"
            "%s\t%li\t# %s\n"
            "%s\t%li\t# %s\n"
            "%s\t%li\t# %s\n"
            "\n",
            expr, n, pthread_self(), getpid(),
            timespec_diff(start.real, end.real),
            timespec_diff(start.cpu, end.cpu),
            timeval_diff(start.rusage.ru_utime, end.rusage.ru_utime),
            timeval_diff(start.rusage.ru_stime, end.rusage.ru_stime),

#define _TIME_THIS_DIFF(name)                                           \
            TOSTRING(name), end.rusage.ru_##name - start.rusage.ru_##name

            _TIME_THIS_DIFF(minflt), "page reclaims (soft page faults)",
            _TIME_THIS_DIFF(majflt), "page faults (hard page faults)",
            _TIME_THIS_DIFF(nswap), "swaps",
            _TIME_THIS_DIFF(inblock), "block input operations",
            _TIME_THIS_DIFF(oublock), "block output operations",
            _TIME_THIS_DIFF(nvcsw), "voluntary context switches",
            _TIME_THIS_DIFF(nivcsw), "involuntary context switches"

#undef _TIME_THIS_DIFF
        );
}
