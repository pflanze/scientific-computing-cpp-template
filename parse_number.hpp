/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/

#ifndef PARSE_NUMBER_HPP_
#define PARSE_NUMBER_HPP_

#include <cstdint>
#include <stdexcept>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <limits>


// C style API
bool parse_int64(const char *str, int64_t *result);

// C++ style API, for various integer types (both signed and unsigned
// are supported)
template<typename T>
T parse_integer(const char *str) {
    const size_t numbytes = sizeof(T);
    assert(numbytes <= 8); // CT, pls
    assert(std::numeric_limits<T>::is_integer);
    int64_t result;
    if (parse_int64(str, &result)) {
        if (std::numeric_limits<T>::is_signed) {
            if (result <= std::numeric_limits<T>::max()) {
                if (result >= std::numeric_limits<T>::min()) {
                    return result;
                } else {
                    throw std::range_error ("number too small for range");
                }
            } else {
                throw std::range_error ("number too large for range");
            }
        } else {
            if (result < 0) {
                throw std::range_error ("number must not be negative");
            }
            // To avoid compiler warnings, cast to unsigned:
            uint64_t uresult = result;
            if (uresult <= std::numeric_limits<T>::max()) {
                if (uresult >= std::numeric_limits<T>::min()) {
                    return result;
                } else {
                    throw std::range_error ("number too small for range");
                }
            } else {
                throw std::range_error ("number too large for range");
            }
        }
    } else {
        throw std::range_error ("invalid number format or number too large");
    }
}


#endif /* PARSE_NUMBER_HPP_ */
