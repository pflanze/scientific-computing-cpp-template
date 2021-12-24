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
#include "time.hpp"
#include "pnm.hpp"


template<typename T>
T square(T x) {
    return x * x;
}


// Mandelbrot set

typedef double mbfloat;

static
unsigned int mandelbrot_numiterations(mbfloat x0, mbfloat y0,
                                      unsigned int maxiter) {
    mbfloat x = 0;
    mbfloat y = 0;
    unsigned int i = 0;
    while ((square(x) + square(y) <= square(2)) && (i < maxiter)) {
        auto xtmp = square(x) - square(y) + x0;
        y = 2*x*y + y0;
        x = xtmp;
        i++;
    }
    //WARN("mandelbrot_numiterations("<<x0<<", "<<y0<<", "<<maxiter<<")="<<i);
    return i;
}

auto mandelbrot_maxiterations =
    env_integer<unsigned int>("maxiterations", 500);
mbfloat mandelbrot_x =
    (mbfloat)env_integer<int64_t>("x_u", -1416000) / 1e6;
mbfloat mandelbrot_y =
    (mbfloat)env_integer<int64_t>("y_u", -50000) / 1e6;
mbfloat mandelbrot_span =
    (mbfloat)env_integer<int64_t>("span_u", 150000) / 1e6;

void
mandelbrot(PGMMatrix8 &m) {
    WARN("x=" << mandelbrot_x << ", " << "y=" << mandelbrot_y << ", "
         << "span=" << mandelbrot_span);
    const auto numrows = m.numrows();
    const auto numcols = m.numcols();
    auto &rows = m.rows();
    const auto maxiter = mandelbrot_maxiterations;
    const auto d = mandelbrot_span / numcols;
    const auto y0 = mandelbrot_y - mandelbrot_span/2;
#pragma omp parallel for schedule(dynamic, 32)
    for (size_t iy = 0; iy < numrows; iy++) {
        auto &row = rows[iy];
        assert (row.size() == numcols);
        const auto y = y0 + iy * d;
        auto x = mandelbrot_x - mandelbrot_span/2;
        for (size_t ix = 0; ix < numcols; ix++) {
            auto val = mandelbrot_numiterations(x, y, maxiter) - 1;
            auto scaled = maxiter <= 256 ? val :
                (((uint64_t)val) * 256) / maxiter;
            assert(scaled < 256);
            row[ix] = scaled;
            x += d;
        }
    }
    m.write_file("mandelbrot.pgm");
}

auto mandelbrot_dim_x =
    env_integer<size_t>("mandelbrot_dim_x", 2000);
auto mandelbrot_dim_y =
    env_integer<size_t>("mandelbrot_dim_y", 2000);

void run_mandelbrot(unsigned int repetitions) {
    PGMMatrix8 m (mandelbrot_dim_x, mandelbrot_dim_y);
    time_this("mandelbrot", [&] {
        mandelbrot(m);
    }/*, repetitions*/);
}


// More standard operations

typedef std::vector<double> vec;

void zero(vec &v) {
    auto n = v.size();
    for (size_t i = 0; i < n; i++) {
        v[i] = 0;
    }
}

void pot3_parallel(vec &a, vec &result) {
    auto n = a.size();
    auto n2 = result.size();
    assert(n == n2);
#pragma omp parallel for
    for (size_t i = 0; i < n; i++) {
        result[i] = square(a[i]);
    }
}

void pot3(vec &a, vec &result) {
    auto n = a.size();
    auto n2 = result.size();
    assert(n == n2);
    for (size_t i = 0; i < n; i++) {
        result[i] = square(a[i]);
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

void bla(size_t n, unsigned int repetitions) {
    vec a;
    a.resize(n);
    auto b = a;

    time_this("t1", [&]() {
        if (env("parallel")) {
#pragma omp parallel for
            for (size_t i = 0; i < n; i++) {
                pot(a, i);
            }
        } else {
            for (size_t i = 0; i < n; i++) {
                pot(a, i);
            }
        }
    }, repetitions);

    time_this("pot2", [&]() {
        pot2(b);
    }, repetitions);

    vec result;
    time_this("result = b", [&]() {
        result = b;
    }, repetitions);

    time_this("pot3", [&]() {
        pot3(b, result);
    }, repetitions);

    time_this("pot3_parallel", [&]() {
        pot3_parallel(b, result);
    }, repetitions);

    run_mandelbrot(repetitions);
}


int main() {
    auto n = env_integer<size_t>("n", 10000000);
    auto repetitions = env_integer<unsigned int>("repetitions", 1);
    std::cout << "n = " << n << std::endl;
    bla(n, repetitions);
    return 0;
}
