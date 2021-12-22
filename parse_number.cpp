/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "parse_number.hpp"

bool parse_int64(const char *str, int64_t *result) {
    int64_t res = atoll(str);
#define BUFS 100
    char buf[BUFS];
    if (snprintf(buf, BUFS, "%" PRIi64, res) >= BUFS)
        return false;
#undef BUFS
    if (strcmp(buf, str) != 0)
        return false;
    *result = res;
    return true;
}

