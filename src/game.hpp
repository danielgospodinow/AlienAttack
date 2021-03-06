#ifndef GAME_HPP
#define GAME_HPP

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
    bool _isGameOver;
    static stack<Scene*> _scenesStack;
};

#endif
