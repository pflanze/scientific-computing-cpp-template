/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/

#ifndef PNM_HPP_
#define PNM_HPP_

#include <string>
#include <vector>

class PGMMatrix8 {
public:
    PGMMatrix8(size_t width, size_t height);
    void write_file(const std::string &path);
    size_t numrows() { return rows_.size(); }
    size_t height() { return rows_.size(); }
    size_t numcols() { return rows_[0].size(); }
    size_t width() { return rows_[0].size(); }
    std::vector<std::vector<uint8_t>> &rows() {
        // XX should not allow size changes!
        return rows_;
    }
private:
    std::vector<std::vector<uint8_t>> rows_;
};


#endif /* PNM_HPP_ */
