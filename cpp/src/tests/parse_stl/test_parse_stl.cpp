#include <iostream>
#include <fmt/core.h>
#include <lib/parse_stl.hpp>

using namespace std;

int main (int argc, char* argv[]) {
  if (argc <= 1) {
    cout << "Provide at least one file path" << endl;
    return 0;
  }
  for (int i = 1; i < argc; i++) {
    parse_stl::ParsedSTL parsed_stl = parse_stl::parse_stl(string(argv[i])).unwrap();
    for (int i; i < HEADER_SIZE; i++) {
      cout << (int) parsed_stl.header[i];
    }
    cout << endl;
    cout << string(parsed_stl.header.data()) << endl;
    cout << parsed_stl.n_triangles << endl;
    for (int i = 0; i < parsed_stl.n_triangles; i++) {
      cout << fmt::format("Triangle {}: ", i);
      for (int j = 0; j < 3; j++) {
        cout << parsed_stl.triangles[i][j].x << ", ";
        cout << parsed_stl.triangles[i][j].y << ", ";
        cout << parsed_stl.triangles[i][j].z << "; ";
      }
      cout << endl;
    }
  }

  return 0;
}