#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SDL2/SDL.h>
#include "lib/utils/result.hpp"
#include <stdint.h>

namespace display {
  struct Display {
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    SDL_Event* event = NULL;
  };

  result::Result<Display> init(int width, int height, std::string window_name);
  
  inline void set_pixel(SDL_Surface* surface, int x, int y, uint32_t pixel_value) { // assuming 32bit pixels
    uint32_t* target_pixel = (uint32_t*) (
      (uint8_t*) surface->pixels
      + y * surface->pitch
      + x * surface->format->BytesPerPixel
    );
    *target_pixel = pixel_value;
    return;
  }

  void update_display(SDL_Window* window, SDL_Surface* surface, SDL_Event* event);
  void close(SDL_Window* window);
}

#endif