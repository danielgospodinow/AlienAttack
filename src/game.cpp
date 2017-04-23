#include "game.hpp"
#include "main_menu_scene.hpp"

stack<Scene*> Game::_scenesStack;

Game::Game()
{
    SDL_Components::init();
    GameUtilities::init();

    SDL_Components::setVolume(10);

    _isGameOver = false;
    pushScene(new MainMenuScene());
}

Game::~Game()
{
    clearScenes();
    GameUtilities::close();
    SDL_Components::close();
}

void Game::startGame()
{
    while(!_isGameOver && SDL_Components::getEvent()->type != SDL_QUIT)
    {
        SDL_PollEvent(SDL_Components::getEvent());
        SDL_RenderClear(SDL_Components::getRenderer());

        if(_scenesStack.size() != 0)
        {
            Scene* currScene = _scenesStack.top();
            if(currScene)
                currScene->update();
        }

        SDL_RenderPresent(SDL_Components::getRenderer());
    }

    SDL_Components::killApp();
}

void Game::pushScene(Scene* scene)
{
    _scenesStack.push(scene);
}

void Game::popScene()
{
    if(_scenesStack.size() == 0)
        return;

    Scene* poppedScene = _scenesStack.top();
    _scenesStack.pop();
    delete poppedScene; // <-- Problemno
}

void Game::clearScenes()
{
    while(_scenesStack.size() > 0)
        popScene();
}
