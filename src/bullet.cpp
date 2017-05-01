#include "bullet.hpp"

Bullet::Bullet(Sprite *sprite, Vec2<int> pos, bool travelUp):
    _sprite(sprite), _pos(pos), _travelUp(travelUp)
{
    _sprite->setPosition(_pos);
    _isDestroyed = false;
    _moveTime = 0.005f;
    _moveTimer = 0;
}

Bullet::~Bullet()
{
    delete _sprite;
}

void Bullet::setPosition(Vec2<int> pos)
{
    _pos = pos;
    _sprite->setPosition(_pos);
}

void Bullet::update(float deltaTime)
{
    _moveTimer += 1 * deltaTime;

    if(_moveTimer > _moveTime)
    {
        if(_travelUp)
        {
            if(_pos.y < 0 -_sprite->getPosnsizeRect().h)
            {
                _isDestroyed = true;
                return;
            }

            setPosition(_pos + Vec2<int>(0, -1));
        }
        else
        {
            if(_pos.y > globals::GAME_HEIGHT)
            {
                _isDestroyed = true;
                return;
            }

            setPosition(_pos + Vec2<int>(0, 1));
        }

        _moveTimer = 0;
    }

    _sprite->draw();
}

bool Bullet::isDestroyed() const {return _isDestroyed;}
Sprite* Bullet::getSprite() const {return _sprite;}

void Bullet::destroy() {_isDestroyed = true;}
