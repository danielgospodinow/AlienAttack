#ifndef GAME_UTILITIES_HPP
#define GAME_UTILITIES_HPP

#include "globals.hpp"
#include "sdl_components.hpp"

class GameUtilities
{
public:
    GameUtilities(SDL_Components* sdlComponents);
    void printText(const char *text, Colors color, Vec2 textLocation, Vec2 textSize);
    SDL_Texture* getText(const char *text, Colors color);
    void renderText(SDL_Texture* texture, Vec2 pos, Vec2 size);

private:
    SDL_Components* _sdlComponents;

    TTF_Font* _font;
    SDL_Surface* _surfaceMessage;
    SDL_Texture* _message;
};

#endif
