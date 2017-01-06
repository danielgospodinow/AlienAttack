#include "player.hpp"

vector<Bullet*> Player::_bullets;

Player::Player(Sprite* sprite, Vec2 pos):
    _sprite(sprite), _pos(pos)
{
    _shootDelay = 0.7f;
    _shootDelayTimer = 0;
    _isAlive = true;
    _shootSound = Mix_LoadWAV("sounds/playerShoot.wav");
    _moveTime = 0.001f;
    _moveTimer = 0;
}

Player::~Player()
{
    delete _sprite;

    for(Uint32 i=0; i<_bullets.size(); i++)
    {
        Bullet* currentBullet = _bullets.at(i);
        if(currentBullet)
            delete currentBullet;
    }

    Mix_FreeChunk(_shootSound);
}

void Player::moveLeft()
{
    if(_moveTimer <= _moveTime)
        return;

    setPosition(_pos + Vec2(-1, 0));
    _moveTimer = 0;

    if(_pos.x <= 0)
    {
        _pos = Vec2(0, _pos.y);
        setPosition(_pos);
    }
}

void Player::moveRight()
{
    if(_moveTimer <= _moveTime)
        return;

    setPosition(_pos + Vec2(1, 0));
    _moveTimer = 0;

    if(_pos.x + _sprite->getPosnsizeRect().w >= globals::GAME_WIDTH)
    {
        _pos = Vec2(globals::GAME_WIDTH - _sprite->getPosnsizeRect().w, _pos.y);
        setPosition(_pos);
    }
}

void Player::drawAndUpdate(float deltaTime)
{
    _moveTimer += 1 * deltaTime;
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

    Mix_PlayChannel(-1, _shootSound, 0);
    _shootDelayTimer = 0;
    _bullets.push_back(new Bullet(new Sprite("sprites/bullet.png", {0,0,4,25}), Vec2(_pos.x + _sprite->getPosnsizeRect().w / 2 - 1, _pos.y - 25)));
}
