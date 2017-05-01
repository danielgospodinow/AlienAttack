#ifndef GAME_UTILITIES_HPP
#define GAME_UTILITIES_HPP

#include "globals.hpp"
#include "sdl_components.hpp"

class GameUtilities
{
public:
    static void init();
    static void close();

    static void renderText(SDL_Texture* texture, SDL_Rect rect, Vec2<int> offset);

    static TTF_Font* const getFont();
    static int getScore();
    static void setScore(int score);
    static int getRandomNumber(int startRange, int endRange);
    static int getStrLen(const char* str);
    static bool areColliding(SDL_Rect one, SDL_Rect two);

private:
    static TTF_Font* _font;
    static int _score;
};

#endif
