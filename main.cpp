/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/

#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <cstdint>
#include <cassert>

#include <vector>
#include "env.hpp"


template<typename T>
T square(T x) {
    return x * x;
}

typedef std::vector<double> vec;

void zero(vec &v) {
    auto n = v.size();
    for (size_t i = 0; i < n; i++) {
        v[i] = 0;
    }
}

void pot2(vec &a) {
    auto n = a.size();
    vec b;
    b.resize(n);
    zero(b);
    for (size_t i = 0; i < n; i++) {
        b[i] = square(a[i]);
    }
}

void pot(vec &a, size_t index) {
    a[index] = square(a[index]);
}

void bla(size_t n) {
    vec a;
    a.resize(n);
    auto b = a;

    if (env("t1")) {
        if (env("parallel")) {
#pragma omp parallel for					\
    shared(a)                                                   \
    schedule(dynamic,20)
            for (size_t i = 0; i < n; i++) {
                pot(a, i);
            }
        } else {
            for (size_t i = 0; i < n; i++) {
                pot(a, i);
            }
        }
    }

    if (env("t2")) {
        pot2(b);
    }
}


int main() {
    size_t n;
    std::cin >> n;
    std::cout << "n = " << n << std::endl;
    bla(n);
    return 0;
}
