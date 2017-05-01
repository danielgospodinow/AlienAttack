#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
#include <functional>
#include <random>
#include <thread>
#include <chrono>
#include "vec2.hpp"
using namespace std;

#define erase_p(pobj) {delete pobj; pobj = NULL;}
typedef unsigned int uint;

enum Colors
{
    White, Blue, Black, Red, Green, Yellow
};

namespace globals
{
    const int GAME_WIDTH = 800;
    const int GAME_HEIGHT = 600;

    const Vec2<int> SCREEN_CENTER = Vec2<int>(GAME_WIDTH / 2, GAME_HEIGHT / 2);

    const float LABEL_HEIGHT_PROPORTION = 1 / 14.0;

    const float LABEL_SCALER = 0.2f;
    const float LABEL_WIDTH_SCALER = 20 * LABEL_SCALER;
    const float LABEL_HEIGHT_SCALER = 30 * LABEL_SCALER;

    const int PLAYER_SPRITE_SIZE_X = 49;
    const int PLAYER_SPRITE_SIZE_Y = 30;
    const int PLAYER_SPEED_PPS = 100;

    const int ENEMY_HORDE_WIDTH = 10;
    const int ENEMY_HORDE_HEIGHT = 5;

    const int BARRICADES_SIZE = 4;

    const int PLAYER_HEALTH = 3;

    const int MAX_HIGHSCORES = 10;
}

#endif
