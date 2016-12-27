#include "game.hpp"
#include "main_menu_scene.hpp"

Game::Game()
{
    _isGameOver = false;
    _sdlComponents = new SDL_Components();
    _gameUtils = new GameUtilities(_sdlComponents);
    _currentScene = Scenes::MainMenu;
}

Game::~Game()
{
    delete _sdlComponents;
    delete _gameUtils;
}

void Game::startGame()
{
    MainMenuScene mms = MainMenuScene(_gameUtils);

    while(!_isGameOver && _sdlComponents->getEvent()->type != SDL_QUIT)
    {
        SDL_PollEvent(_sdlComponents->getEvent());
        SDL_RenderClear(_sdlComponents->getRenderer());

        switch(_currentScene)
        {
        case Scenes::MainMenu: mms.update(); break;
        case Scenes::Credits: break;
        case Scenes::MultiplayScene: break;
        case Scenes::SinglePlayScene: break;
        };

        SDL_RenderPresent(_sdlComponents->getRenderer());
    }

    SDL_Quit();
    exit(0);
}
