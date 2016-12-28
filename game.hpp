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
    void gameOver() {_isGameOver = false;}

    static void pushScene(Scene* scene);
    static void popScene();
    static void clearScenes();

private:
    SDL_Components* _sdlComponents;
    GameUtilities* _gameUtils;
    bool _isGameOver;
    static stack<Scene*> _scenesStack;
};

#endif
