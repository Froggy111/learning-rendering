#ifndef PARSE_STL_HPP
#define PARSE_STL_HPP

#include <vector>
#include <array>
#include <cstdint>
#include "lib/utils/result.hpp"

#define HEADER_SIZE 80
#define NUM_BYTES_PER_TRIANGLE 50
#define STL_TEXT_FORM_STARTING_SEQUENCE "solid"

namespace parse_stl {
  struct Point {
    float x = 0;
    float y = 0;
    float z = 0;
  };

  struct ParsedSTL {
    std::vector<std::array<Point, 3>> triangles;
    uint64_t n_triangles = 0;
    std::vector<char> header;
  };

  result::Result<ParsedSTL> parse_stl(std::string file_path);
}

#endif