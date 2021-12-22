/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/

#ifndef TIME_HPP_
#define TIME_HPP_

#include <sys/time.h>
#include <sys/resource.h>
#include <functional>
#include "util.hpp"


struct Timestamp {
    struct timespec real;
    struct timespec cpu;
    struct rusage rusage;
};

struct Timestamp get_timestamp();

void time_print(const char *expr,
                struct Timestamp &start,
                struct Timestamp &end,
                int n);

template<typename T>
static
T time_this_(const char *expr, std::function<T()> thunk, int n = 1) {
    auto start = get_timestamp();
    T res;
    for (int i = 0; i < n; i++) {
        res = thunk();
    }
    auto end = get_timestamp();
    time_print(expr, start, end, n);
    return res;
}

UNUSED static
void time_this(const char *expr, std::function<void()> thunk, int n = 1) {
    time_this_<int>(expr, [&]() {
        thunk();
        return 0;
    }, n);
}

#define TIME(expr) time_this<R>(TOSTRING(expr), [&]() -> R {return expr; })


#endif /* TIME_HPP_ */
