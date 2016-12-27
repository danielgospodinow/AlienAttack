#include "game.hpp"
#include "main_menu_scene.hpp"

Game::Game()
{
    _isGameOver = false;
    _sdlComponents = new SDL_Components();
    _gameUtils = new GameUtilities(_sdlComponents);

    scenesStack.push(new MainMenuScene(_gameUtils));
}

Game::~Game()
{
    delete _sdlComponents;
    delete _gameUtils;
}

void Game::startGame()
{
    while(!_isGameOver && _sdlComponents->getEvent()->type != SDL_QUIT)
    {
        SDL_PollEvent(_sdlComponents->getEvent());
        SDL_RenderClear(_sdlComponents->getRenderer());

        if(scenesStack.size() != 0)
        {
            Scene* currScene = scenesStack.top();
            currScene->update();
        }

        SDL_RenderPresent(_sdlComponents->getRenderer());
    }

    _sdlComponents->killApp();
}
