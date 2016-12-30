#include "game.hpp"
#include "main_menu_scene.hpp"

stack<Scene*> Game::_scenesStack;

Game::Game()
{
    _isGameOver = false;
    _sdlComponents = new SDL_Components();
    _gameUtils = new GameUtilities(_sdlComponents);

    pushScene(new MainMenuScene(_gameUtils));
}

Game::~Game()
{
    delete _sdlComponents;
    delete _gameUtils;
    clearScenes();
}

void Game::startGame()
{
    while(!_isGameOver && _sdlComponents->getEvent()->type != SDL_QUIT)
    {
        SDL_PollEvent(_sdlComponents->getEvent());
        SDL_RenderClear(_sdlComponents->getRenderer());

        if(_scenesStack.size() != 0)
        {
            Scene* currScene = _scenesStack.top();
            currScene->update();
        }

        SDL_RenderPresent(_sdlComponents->getRenderer());
    }

    _sdlComponents->killApp();
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
    delete poppedScene;
}

void Game::clearScenes()
{
    while(_scenesStack.size() > 0)
        popScene();
}
