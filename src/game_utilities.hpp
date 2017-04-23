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
    static int getRandomNumber(int startRange, int endRange);
    static TTF_Font* const getFont() {return _font;}
    static int getStrLen(const char* str);
    static bool areColliding(SDL_Rect one, SDL_Rect two);
    static int getScore() {return _score;}
    static void setScore(int score) {_score = score;}

private:
    static TTF_Font* _font;
    static int _score;
};

#endif
