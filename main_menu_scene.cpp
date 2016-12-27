#include "main_menu_scene.hpp"

void MainMenuScene::update()
{
    const char* introText = "Welcome to Alien Attack!";
    Vec2 introTextSize(globals::GAME_WIDTH * 0.8f, globals::GAME_HEIGHT * 0.1f);
    Vec2 introTextPos(globals::GAME_WIDTH/2 - introTextSize.x/2, globals::GAME_HEIGHT * 0.15f);
    _gameUtils->printText(introText, Colors::White, introTextPos, introTextSize);

    const char* madeByText = "Developed by Daniel Gospodinow - 81531";
    Vec2 madeByTextSize(370, 22);
    Vec2 madeByTextPos(globals::GAME_WIDTH - madeByTextSize.x * 1.02f, globals::GAME_HEIGHT - madeByTextSize.y * 1.1f);
    _gameUtils->printText(madeByText, Colors::Red, madeByTextPos, madeByTextSize);
}
