#ifndef GAME_HPP
#define GAME_HPP

#include "globals.hpp"
#include "sdl_components.hpp"
#include "game_utilities.hpp"

enum Scenes {MainMenu, Credits, SinglePlayScene, MultiplayScene};

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
    Scenes _currentScene;
    bool _isGameOver;
};

#endif
