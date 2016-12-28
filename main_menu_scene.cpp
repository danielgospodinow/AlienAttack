#include "main_menu_scene.hpp"

MainMenuScene::MainMenuScene(GameUtilities *gameUtils): Scene(gameUtils)
{
    float labelHeightProportion = 1 / 14.0;

    _introLabel = _gameUtils->getText("Welcome to Alien Attack!", Colors::White);
    _introTextSize = Vec2(globals::GAME_WIDTH * 0.8f, 0);
    _introTextSize.y = _introTextSize.x * labelHeightProportion;
    _introTextPos = Vec2(globals::GAME_WIDTH/2 - _introTextSize.x/2, globals::GAME_HEIGHT * 0.15f);

    _creditsLabel = _gameUtils->getText("Developed by Daniel Gospodinow - 81531", Colors::Red);
    _creditsTextSize = Vec2(200, 0);
    _creditsTextSize.y = _creditsTextSize.x * labelHeightProportion;
    _creditsTextPos = Vec2(globals::GAME_WIDTH - _creditsTextSize.x * 1.02f, globals::GAME_HEIGHT - _creditsTextSize.y * 1.1f);
}

MainMenuScene::~MainMenuScene()
{
    SDL_DestroyTexture(_introLabel);
    SDL_DestroyTexture(_creditsLabel);
}

void MainMenuScene::update()
{
    _gameUtils->renderText(_introLabel, _introTextPos, _introTextSize);
    _gameUtils->renderText(_creditsLabel, _creditsTextPos, _creditsTextSize);
}
