/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/

#ifndef ENV_HPP_
#define ENV_HPP_

#include "parse_number.hpp"

// Return true iff the environment variable with the given name is set
// to "1"
bool env(const char* name);

// Return the integer value the environment variable is set to, or
// deflt if unset. Throws exceptions if input is set but invalid.
template<typename T>
T env_integer(const char* name, T deflt) {
    auto val = getenv(name);
    if (val) {
        if (*val) {
            return parse_integer<T>(val);
        } else {
            return deflt;
        }
    } else {
        return deflt;
    }
}

#endif /* ENV_HPP_ */
