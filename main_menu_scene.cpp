#include "main_menu_scene.hpp"

MainMenuScene::MainMenuScene(GameUtilities *gameUtils): Scene(gameUtils)
{
    _introLabel = new Label("Welcome to Alien Attack!", Vec2(globals::SCREEN_CENTER.x, 0), Colors::White, 7);
    _introLabel->setOffset(Vec2(0, -_introLabel->getRect().y * 3));

    _creditsLabel = new Label("Developed by Daniel Gospodinow - 81531", Vec2(globals::GAME_WIDTH, globals::GAME_HEIGHT), Colors::White, 2);
    _creditsLabel->setOffset(Vec2(-_creditsLabel->getRect().w / 1.8f, -_creditsLabel->getRect().h * 1.5f));

    //_playSPButton = new Button(new Label(), _gameUtils);
//    _playMPButton = new Button();
//    _creditialsButton = new Button();
//    _exitButton = new Button();
}

MainMenuScene::~MainMenuScene()
{
    delete _introLabel;
    delete _creditsLabel;
    delete _creditialsButton;
    delete _playSPButton;
    delete _playMPButton;
    delete _exitButton;
}

void MainMenuScene::update()
{
    _gameUtils->renderText(_introLabel->getTexture(), _introLabel->getRect(), _introLabel->getOffset());
    _gameUtils->renderText(_creditsLabel->getTexture(), _creditsLabel->getRect(), _creditsLabel->getOffset());

//    _playSPButton->update();
//    _playMPButton->update();
//    _creditialsButton->update();
//    _exitButton->update();
}
