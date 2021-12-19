#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <cstdint>
#include <cassert>

#include <vector>


bool env(const char* name) {
    auto val = getenv(name);
    if (val) {
        if (*val) {
            return *val == '1';
        } else {
            return false;
        }
    } else {
        return false;
    }
}


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
        for (size_t i = 0; i < n; i++) {
            pot(a, i);
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
