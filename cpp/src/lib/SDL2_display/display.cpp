#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <stdint.h>
#include <fmt/core.h>
#include "lib/SDL2_display/display.hpp"

namespace display {
  using namespace fmt;
  result::Result<Display> init(int width, int height, std::string window_name) {
    SDL_Window* window = NULL;
    SDL_Surface* screen_surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      return result::error<Display>(format("SDL could not initialize. SDL_Error: {}", SDL_GetError()), __PRETTY_FUNCTION__);
    }
    window = SDL_CreateWindow(window_name.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
      return result::error<Display>(format("SDL window could not be created. SDL_Error: {}", SDL_GetError()), __PRETTY_FUNCTION__);
    }
    screen_surface = SDL_GetWindowSurface(window);

    SDL_Event event;
    SDL_Event* event_ptr = &event;

    Display display = {window, screen_surface, event_ptr};
    return result::success<Display>(display, __PRETTY_FUNCTION__);
  }

  void update_display(SDL_Window* window, SDL_Surface* surface, SDL_Event* event) {
    if (SDL_UpdateWindowSurface(window) < 0) {
      result::panic(format("SDL update window surface failed. SDL_Error: {}", SDL_GetError()), __PRETTY_FUNCTION__);
    }

    if (SDL_PollEvent(event)) {
      if (event->type == SDL_QUIT) {
        close(window);
        result::panic("User closed window", __PRETTY_FUNCTION__);
      }
    }
    return;
  }

  void close(SDL_Window* window) {
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    return;
  }
}