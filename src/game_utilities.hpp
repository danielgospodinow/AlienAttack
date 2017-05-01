#ifndef GAME_UTILITIES_HPP
#define GAME_UTILITIES_HPP

#include "globals.hpp"
#include "sdl_components.hpp"
#include <fstream>

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

    static void updateHighScores();
    static int* getHighscores();

    template <typename T>
    static void selectionSort(T* arr, int size);
    template <typename T>
    static void swap(T& one, T& two);

    static void printScore() //temp meth for debugging in main_menu_scene
    {
        for(int i=0; i<globals::MAX_HIGHSCORES; i++)
            cout << _highScores[i] << endl;
    }

private:
    GameUtilities() {}

    static void readHighScores();
    static void writeHighScores();

    static TTF_Font* _font;
    static int _score;

    static const char* _highScoresFilePath;
    static int _highScores[globals::MAX_HIGHSCORES];
};

#endif
