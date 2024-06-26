#include <vector>
#include <array>
#include <cstdint>
#include <string>
#include <fstream>
#include <fmt/core.h>
// #include "lib/utils/result.hpp"
#include "lib/parse_stl.hpp"

namespace parse_stl {
  using namespace std;
  using namespace fmt;

  result::Result<ParsedSTL> parse_stl(string file_path) {
    if (!file_path.ends_with(".stl")) {
      return result::error<ParsedSTL>(format("File '{}' is not an STL file", file_path), __PRETTY_FUNCTION__);
    }
    ifstream file(file_path, ios::ate | ios::binary);
    if (!file) {
      return result::error<ParsedSTL>(format("No file at file path '{}'", file_path), __PRETTY_FUNCTION__);
    }
    long size = file.tellg();
    if (size < (HEADER_SIZE + 4)) {
      return result::error<ParsedSTL>(format("STL file '{}' is not valid", file_path), __PRETTY_FUNCTION__);
    }
    file.seekg(0, ios::beg);

    ParsedSTL parsed_stl;
    
    parsed_stl.header.resize(HEADER_SIZE);
    file.read(&parsed_stl.header[0], HEADER_SIZE);
    parsed_stl.header.push_back('\0');
    string header_str(parsed_stl.header.data());
    string text_header_str = STL_TEXT_FORM_STARTING_SEQUENCE;
    if (header_str.starts_with(text_header_str)) {
      return result::error<ParsedSTL>(format("STL file '{}' is in text form. It needs to be in binary form.", file_path), __PRETTY_FUNCTION__);
    }

    file.read((char*) &parsed_stl.n_triangles, 4);
    if (size < (HEADER_SIZE + 4 + parsed_stl.n_triangles * NUM_BYTES_PER_TRIANGLE)) {
      return result::error<ParsedSTL>(format("STL file '{}' has mismatched triangle count and size", file_path), __PRETTY_FUNCTION__);
    }

    char triangle_tmp[4] = {0};
    for (uint64_t i = 0; i < parsed_stl.n_triangles; i++) {
      int start_pos = HEADER_SIZE + 4 + NUM_BYTES_PER_TRIANGLE * i + 4 * 3;
      array<Point, 3> triangle;
      file.seekg(start_pos, ios::beg);
      for (uint8_t i = 0; i < 3; i++) {
        file.read(triangle_tmp, 4);
        triangle[i].x = *(float*) triangle_tmp;
        file.read(triangle_tmp, 4);
        triangle[i].y = *(float*) triangle_tmp;
        file.read(triangle_tmp, 4);
        triangle[i].z = *(float*) triangle_tmp;
        parsed_stl.triangles.push_back(triangle);
      }
    }
    return result::success<ParsedSTL>(parsed_stl, __PRETTY_FUNCTION__);
  }
}