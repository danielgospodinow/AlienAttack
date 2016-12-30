#include "main_menu_scene.hpp"

MainMenuScene::MainMenuScene(GameUtilities *gameUtils): Scene(gameUtils)
{
    _introLabel = new Label("Welcome to Alien Attack!", Vec2(globals::SCREEN_CENTER.x, 0), Colors::White, 7);
    _introLabel->setOffset(Vec2(0, -_introLabel->getRect().y * 3));

    _creditsLabel = new Label("Developed by Daniel Gospodinow - 81531", Vec2(globals::GAME_WIDTH, globals::GAME_HEIGHT), Colors::White, 2);
    _creditsLabel->setOffset(Vec2(-_creditsLabel->getRect().w / 1.8f, -_creditsLabel->getRect().h * 1.5f));

    _playSPButton = new Button(new Label("Single-player", Vec2(globals::SCREEN_CENTER), Colors::Red, 5), _gameUtils);
    _playSPButton->getLabel()->setOffset(Vec2(0, (_playSPButton->getLabel()->getRect().h * -2)));

    _playMPButton = new Button(new Label("Multiplayer", Vec2(globals::SCREEN_CENTER), Colors::Red, 5), _gameUtils);

    _creditialsButton = new Button(new Label("Credits", Vec2(globals::SCREEN_CENTER), Colors::Red, 5), _gameUtils);
    _creditialsButton->getLabel()->setOffset(Vec2(0, (_creditialsButton->getLabel()->getRect().h * 2)));
}

MainMenuScene::~MainMenuScene()
{
    delete _introLabel;
    delete _creditsLabel;
    delete _creditialsButton;
    delete _playSPButton;
    delete _playMPButton;
}

void MainMenuScene::update()
{
    _gameUtils->renderText(_introLabel->getTexture(), _introLabel->getRect(), _introLabel->getOffset());
    _gameUtils->renderText(_creditsLabel->getTexture(), _creditsLabel->getRect(), _creditsLabel->getOffset());

    _playSPButton->update();
    _playMPButton->update();
    _creditialsButton->update();
}
