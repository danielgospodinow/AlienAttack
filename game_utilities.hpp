#ifndef GAME_UTILITIES_HPP
#define GAME_UTILITIES_HPP

#include "globals.hpp"
#include "sdl_components.hpp"

class GameUtilities
{
public:
    GameUtilities(SDL_Components* sdlComponents);
    void printText(const char *text, Colors color, Vec2 textLocation, Vec2 textSize);

private:
    SDL_Components* _sdlComponents;

    TTF_Font* _font;
    SDL_Surface* _surfaceMessage;
    SDL_Texture* _message;
};

#endif
