#ifndef GAME_UTILITIES_HPP
#define GAME_UTILITIES_HPP

#include "globals.hpp"
#include "sdl_components.hpp"

class GameUtilities
{
public:
    GameUtilities(SDL_Components* sdlComponents);
    ~GameUtilities() {TTF_CloseFont(_font); SDL_FreeSurface(_surfaceMessage); SDL_DestroyTexture(_message);}
    void printText(const char *text, Colors color, Vec2 textLocation, Vec2 textSize);
    SDL_Texture* getText(const char *text, Colors color);
    static void renderText(SDL_Texture* texture, SDL_Rect rect, Vec2 offset);
    static int getRandomNumber(int startRange, int endRange);
    static TTF_Font* const getFont() {return _font;}
    static int getStrLen(const char* str);
    static bool areColliding(SDL_Rect one, SDL_Rect two);

private:
    SDL_Components* _sdlComponents;

    static TTF_Font* _font;
    SDL_Surface* _surfaceMessage;
    SDL_Texture* _message;
};

#endif
