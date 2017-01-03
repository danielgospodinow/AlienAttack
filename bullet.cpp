#include "bullet.hpp"

Bullet::Bullet(Sprite *sprite, Vec2 pos, bool travelUp):
    _sprite(sprite), _pos(pos), _travelUp(travelUp)
{
    _sprite->setPosition(_pos);
    _isDestroyed = false;
}

Bullet::~Bullet()
{
    delete _sprite;
}

void Bullet::setPosition(Vec2 pos)
{
    _pos = pos;
    _sprite->setPosition(_pos);
}

void Bullet::update(float deltaTime)
{
    if(_travelUp)
    {
        if(_pos.y < 0 -_sprite->getPosnsizeRect().h)
        {
            _isDestroyed = true;
            return;
        }

        setPosition(_pos + Vec2(0, -globals::PLAYER_SPEED_PPS * deltaTime * 10));
    }
    else
    {
        if(_pos.y > globals::GAME_HEIGHT)
        {
            _isDestroyed = true;
            return;
        }

        setPosition(_pos + Vec2(0, globals::PLAYER_SPEED_PPS * deltaTime * 10));
    }

    _sprite->draw();
}
