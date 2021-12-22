/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/

#include <string.h>
#include "util.hpp"
#include "err.hpp"

void throwWithStrerror(const std::string &msg) {
#define BUFLEN 1024
      char err[BUFLEN];
      strerror_r(errno, err, BUFLEN);
      err[BUFLEN-1] = 0;
      throw std::ios_base::failure(STR(msg << ": " << err));
#undef BUFLEN
}


