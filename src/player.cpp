#include "player.hpp"

vector<Bullet*> Player::_bullets;

Player::Player(Sprite* sprite, Vec2<int> pos):
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

    for(uint i=0; i<_bullets.size(); i++)
    {
        Bullet* currentBullet = _bullets.at(i);
        if(currentBullet)
            delete currentBullet;
    }
    _bullets.clear();

    Mix_FreeChunk(_shootSound);
}

void Player::moveLeft()
{
    if(_moveTimer <= _moveTime)
        return;

    setPosition(_pos + Vec2<int>(-1, 0));
    _moveTimer = 0;

    if(_pos.x <= 0)
    {
        _pos = Vec2<int>(0, _pos.y);
        setPosition(_pos);
    }
}

void Player::moveRight()
{
    if(_moveTimer <= _moveTime)
        return;

    setPosition(_pos + Vec2<int>(1, 0));
    _moveTimer = 0;

    if(_pos.x + _sprite->getPosnsizeRect().w >= globals::GAME_WIDTH)
    {
        _pos = Vec2<int>(globals::GAME_WIDTH - _sprite->getPosnsizeRect().w, _pos.y);
        setPosition(_pos);
    }
}

void Player::drawAndUpdate(float deltaTime)
{
    _moveTimer += 1 * deltaTime;
    _shootDelayTimer += 1 * deltaTime;

    for (uint i=0; i < _bullets.size(); i++)
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
    _bullets.push_back(new Bullet(new Sprite("sprites/bullet.png", {0,0,4,25}), Vec2<int>(_pos.x + _sprite->getPosnsizeRect().w / 2 - 1, _pos.y - 25)));
}

Sprite* Player::getSprite() const
{
    return _sprite;
}

Vec2<int> Player::getPosition() const
{
    return _pos;
}

bool Player::isAlive() const
{
    return _isAlive;
}

void Player::setPosition(Vec2<int> pos)
{
    _pos = pos;
    _sprite->setPosition(pos);
}

std::vector<Bullet*> Player::getBullets()
{
    return _bullets;
}

void Player::kill()
{
    _isAlive = false;
}
