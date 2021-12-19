#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <cstdint>
#include <cassert>

#include <vector>


int foo(int n) {
    std::vector<float> v;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        v[i] = 12.345;
    }
    return 0;
}


int main() {
    int n;
    std::cin >> n;
    std::cout << "n = " << n << std::endl;
    foo(n);
    return 0;
}
