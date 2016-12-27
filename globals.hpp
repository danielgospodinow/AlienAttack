#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

using namespace std;

#include "vec2.hpp"

enum Colors
{
    White, Blue, Black, Red, Green, Yellow
};

namespace globals
{
    const int GAME_WIDTH = 800;
    const int GAME_HEIGHT = 600;
}

#endif
