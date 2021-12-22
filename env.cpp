/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/

#include <stdlib.h>
#include "env.hpp"

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

