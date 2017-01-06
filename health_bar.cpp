#include "health_bar.h"

HealthBar::HealthBar(int lives):
    _lives(lives)
{
    _healthBar = new Sprite("sprites/currentSprites.png", {0, 0, globals::PLAYER_SPRITE_SIZE_X/2, globals::PLAYER_SPRITE_SIZE_Y/2}, {0,685,104,64});
    _pos = Vec2(globals::GAME_WIDTH - globals::PLAYER_SPRITE_SIZE_X/2 * 1.2f, _healthBar->getPosnsizeRect().h * 0.8f);
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
        _healthBar->setPosition(_healthBar->getPosition() + Vec2(-_healthBar->getPosnsizeRect().w * 1.2f, 0));
    }
    _healthBar->setPosition(_pos);
}

void HealthBar::reduce()
{
    _lives -= 1;
}
