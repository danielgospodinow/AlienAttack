#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <stack>

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

    const Vec2 SCREEN_CENTER = Vec2(GAME_WIDTH / 2, GAME_HEIGHT / 2);

    const float LABEL_HEIGHT_PROPORTION = 1 / 14.0;

    const float LABEL_SCALER = 0.2f;
    const float LABEL_WIDTH_SCALER = 20 * LABEL_SCALER;
    const float LABEL_HEIGHT_SCALER = 30 * LABEL_SCALER;
}

#endif
