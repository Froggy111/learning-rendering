#include <iostream>
#include <string>
#include <stdint.h>
#include <fmt/core.h>
#include <lib/SDL2_display/display.hpp>
#include <lib/utils/result.hpp>
#include <chrono>

using namespace std;
using namespace fmt;

int main(int argc, char* argv[]) {
  /*
  //*ARGS:
  1. window width in pixels
  2. window height in pixels
  3. R
  4. G
  5. B
  6. A
  7. number of frames
  8. window name
  */
  if (argc != 9) {
    result::panic("Invalid number of arguments. Args:\n1. window width in pixels\n2. window height in pixels\n3. R\n4. G\n5. B\n6. A\n7. number of frames\n8. window name", __PRETTY_FUNCTION__);
    return 0;
  }

  try{
    int width = stoi(argv[1]);
    int height = stoi(argv[2]);
    uint8_t r = stoi(argv[3]);
    uint8_t g = stoi(argv[4]);
    uint8_t b = stoi(argv[5]);
    uint8_t a = stoi(argv[6]);
    int n_frames = stoi(argv[7]);
  }
  catch (exception &err) {
    result::panic("Conversion error, arguments invalid. Args:\n1. window width in pixels\n2. window height in pixels\n3. R\n4. G\n5. B\n6. A\n7. number of frames\n8. window name", __PRETTY_FUNCTION__);
    return 0;
  }

  int width = stoi(argv[1]);
  int height = stoi(argv[2]);
  uint8_t r = stoi(argv[3]);
  uint8_t g = stoi(argv[4]);
  uint8_t b = stoi(argv[5]);
  uint8_t a = stoi(argv[6]);
  int n_frames = stoi(argv[7]);

  display::Display disp = display::init(width, height, argv[8]).unwrap();

  auto start = chrono::system_clock::now();

  for (int i = 0; i < n_frames; i++) {
    float brightness = 1 - (float) i / n_frames;
    uint8_t r_tmp = r * brightness;
    uint8_t g_tmp = g * brightness;
    uint8_t b_tmp = b * brightness;
    uint32_t pixel = SDL_MapRGBA(disp.surface->format, r_tmp, g_tmp, b_tmp, r_tmp);
    cout << format("current brightness: {}", brightness) << endl;
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        // display::set_pixel_rgba_brightness(disp.surface, x, y, r, g, b, a, brightness);
        display::set_pixel(disp.surface, x, y, pixel);
      }
    }
    display::update_display(disp.window, disp.surface, disp.event);
  }

  auto end = chrono::system_clock::now();
  auto elapsed = end - start;
  cout << format("time passed: {}", elapsed.count()) << endl;
  cout << format("FPS: {}", n_frames / (elapsed.count() / 1e9)) << endl;
  
  display::close(disp.window);
}