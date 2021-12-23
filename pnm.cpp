/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/

#include <fstream>
#include "pnm.hpp"

PGMMatrix8::PGMMatrix8(size_t width, size_t height) {
    rows_.resize(height);
    for (auto &row : rows_) {
        row.resize(width);
    }
}

void
PGMMatrix8::write_file(const std::string &path) {
    std::ofstream out(path);
    out << "P5\n# PGMMatrix8 from pnm.cpp\n"
        << width() << " " << height() << "\n"
        << 255 << "\n";
    for (auto &row : rows_) {
        for (auto &greyvalue : row) {
            out << (unsigned char)greyvalue;
        }
    }
    out.close();
}
