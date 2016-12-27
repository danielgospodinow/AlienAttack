#ifndef GAME_HPP
#define GAME_HPP

#include "globals.hpp"
#include "sdl_components.hpp"
#include "game_utilities.hpp"
#include "scene.hpp"

class Game
{
public:
    Game();
    ~Game();

    void startGame();
    void gameOver() {this->_isGameOver = false;}

private:
    SDL_Components* _sdlComponents;
    GameUtilities* _gameUtils;
    bool _isGameOver;
    stack<Scene*> scenesStack;
};

#endif
