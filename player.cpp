#include "player.hpp"

Player::Player(Sprite* sprite, Vec2 pos):
    _sprite(sprite), _pos(pos)
{
    _shootDelay = 0.7f;
    _shootDelayTimer = 0;
}

Player::~Player()
{
    delete _sprite;
}

void Player::moveLeft(float deltaTime)
{
    setPosition(_pos + Vec2(-globals::PLAYER_SPEED_PPS * deltaTime * 10, 0));

    if(_pos.x <= 0)
    {
        _pos = Vec2(0, _pos.y);
        setPosition(_pos);
    }
}

void Player::moveRight(float deltaTime)
{
    setPosition(_pos + Vec2(globals::PLAYER_SPEED_PPS * deltaTime * 10, 0));

    if(_pos.x + _sprite->getPosnsizeRect().w >= globals::GAME_WIDTH)
    {
        _pos = Vec2(globals::GAME_WIDTH - _sprite->getPosnsizeRect().w, _pos.y);
        setPosition(_pos);
    }
}

void Player::drawAndUpdate(float deltaTime)
{
    _shootDelayTimer += 1 * deltaTime;

    for (Uint32 i=0; i < _bullets.size(); i++)
    {
        Bullet* currentBullet = _bullets[i];

        if(currentBullet->isDestroyed())
        {
            _bullets.erase(std::remove(_bullets.begin(), _bullets.end(), currentBullet), _bullets.end());
            delete currentBullet;
            continue;
        }

        currentBullet->update(deltaTime);
    }

    _sprite->draw();
}

void Player::shoot()
{
    if(_shootDelayTimer <= _shootDelay)
        return;

    _shootDelayTimer = 0;
    _bullets.push_back(new Bullet(new Sprite("sprites/bullet.png", {0,0,4,25}), Vec2(_pos.x + _sprite->getPosnsizeRect().w / 2 - 1, _pos.y - 25)));
}
