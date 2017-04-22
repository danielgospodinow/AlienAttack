#include "ui.hpp"

UI::UI(bool multiplayer)
{
    initScoreBoard();
    initHealthBars(multiplayer);
}

UI::~UI()
{
    delete _scoreTextLabel;
    delete _scoreNumLabel;
    delete _hpBarP1;
    delete _hpBarP2;
}

void UI::reduceHealthBarOne()
{
    _hpBarP1->reduce();
}

void UI::reduceHealthBarTwo()
{
    _hpBarP2->reduce();
}

int UI::getPlayerOneLives()
{
    return _hpBarP1->getLives();
}

int UI::getPlayerTwoLives()
{
    return _hpBarP2->getLives();
}

void UI::drawHealthBars()
{
    _hpBarP1->update();
    _hpBarP2->update();
}

void UI::initHealthBars(bool multiplayer)
{
    _hpBarP1 = new HealthBar(globals::PLAYER_HEALTH);

    if(multiplayer)
        _hpBarP2 = new HealthBar(globals::PLAYER_HEALTH, true);
    else
        _hpBarP2 = new HealthBar(-1, true);
}

void UI::updateScoreBoard(int newScore)
{
    _scoreNumLabel->setText(to_string(newScore).c_str());
}

void UI::drawScoreBoard()
{
    GameUtilities::renderText(_scoreTextLabel->getTexture(), _scoreTextLabel->getRect(), _scoreTextLabel->getOffset());
    GameUtilities::renderText(_scoreNumLabel->getTexture(), _scoreNumLabel->getRect(), _scoreNumLabel->getOffset());
}

void UI::initScoreBoard()
{
    _scoreTextLabel = new Label("Score: ", Vec2<int>(0, 0), Colors::White, 3);
    _scoreTextLabel->setOffset(Vec2<int>(_scoreTextLabel->getRect().w / 1.9f, _scoreTextLabel->getRect().h * 0.8f));
    _scoreNumLabel = new Label("0", Vec2<int>(_scoreTextLabel->getPos().x + _scoreTextLabel->getRect().w * 1.5f, _scoreTextLabel->getOffset().y), Colors::Green, 3);
}
