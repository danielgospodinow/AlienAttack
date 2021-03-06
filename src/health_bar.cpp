#include "health_bar.hpp"

HealthBar::HealthBar(int lives,  bool playerTwo):
    _lives(lives)
{
    _healthBar = new Sprite("sprites/currentSprites.png", {0, 0, globals::PLAYER_SPRITE_SIZE_X/2, globals::PLAYER_SPRITE_SIZE_Y/2}, {0,685,104,64});
    if(!playerTwo)
        _pos = Vec2<int>(globals::GAME_WIDTH - globals::PLAYER_SPRITE_SIZE_X/2 * 1.2f, _healthBar->getPosnsizeRect().h * 0.8f);
    else
        _pos = Vec2<int>(globals::GAME_WIDTH - globals::PLAYER_SPRITE_SIZE_X/2 * 1.2f, _healthBar->getPosnsizeRect().h * 0.8f + _healthBar->getPosnsizeRect().h * 1.3f);
    _healthBar->setPosition(_pos);
}

HealthBar::~HealthBar()
{
    delete _healthBar;
}

void HealthBar::update()
{
    for(int i=0; i<_lives; i++)
    {
        _healthBar->draw();
        _healthBar->setPosition(_healthBar->getPosition() + Vec2<int>(-_healthBar->getPosnsizeRect().w * 1.2f, 0));
    }
    _healthBar->setPosition(_pos);
}

void HealthBar::reduce()
{
    if(_lives <= -1)
        return;

    _lives -= 1;
}

int HealthBar::getLives() const {return _lives;}
