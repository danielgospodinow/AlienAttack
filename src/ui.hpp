#ifndef UI_HPP
#define UI_HPP

#include "globals.hpp"
#include "label.hpp"
#include "health_bar.h"

class UI
{
public:
    UI(bool multiplayer = false);
    ~UI();

    void updateScoreBoard(int newScore);
    void drawScoreBoard();

    void drawHealthBars();
    void reduceHealthBarOne();
    void reduceHealthBarTwo();

    int getPlayerOneLives();
    int getPlayerTwoLives();

private:
    void initScoreBoard();
    void initHealthBars(bool multiplayer);

    Label* _scoreTextLabel;
    Label* _scoreNumLabel;

    HealthBar* _hpBarP1;
    HealthBar* _hpBarP2;
};

#endif
