#include "enemy.hpp"

Enemy::Enemy(EnemyTypes enemyType, Vec2 position):
    _pos(position), _enemyType(enemyType)
{
    _isHit = false;
    _spriteLocation = "sprites/currentSprites.png";

    switch(_enemyType)
    {
    case Radkata: _sizeRect = {_pos.x, _pos.y, 25, 25}; _cropRect01 = {45, 0, 64, 63}; _cropRect02 = {147, 0, 64, 64}; break;
    case Sashkata: _sizeRect = {_pos.x, _pos.y, 34, 25}; _cropRect01 = {32, 103, 88, 64}; _cropRect02 = {136, 103, 88, 64}; break;
    case Kirkata: _sizeRect = {_pos.x, _pos.y, 37, 25}; _cropRect01 = {19, 210, 96, 64}; _cropRect02 = {133 ,211, 96, 64}; break;
    case Genio: _sizeRect = {_pos.x, _pos.y, 73, 32}; _cropRect01 = {35, 307, 192, 84}; _cropRect02 = {35, 307, 192, 84}; break;
    }

    _sprite01 = new Sprite(_spriteLocation, _sizeRect, _cropRect01);
    _sprite02 = new Sprite(_spriteLocation, _sizeRect, _cropRect02);

    _isSpriteState01 = true;
    _spriteTransitionTimer = 0;
    _spriteTransitionTime = 1;
}

Enemy::~Enemy()
{
    delete _sprite01;
    delete _sprite02;

    for(int i=_bullets.size() - 1; i>=0; i--)
    {
        Bullet* currentBullet = _bullets.at(i);
        _bullets.pop_back();
        delete currentBullet;
    }
}

void Enemy::update(float deltaTime)
{
    _spriteTransitionTimer += 1 * deltaTime;
    if(_spriteTransitionTimer >= _spriteTransitionTime)
    {
        _spriteTransitionTimer = 0;
        _isSpriteState01 = !_isSpriteState01;
    }

    _sprite01->setPosition(_pos);
    _sprite02->setPosition(_pos);

    if(_isSpriteState01)
        _sprite01->draw();
    else
        _sprite02->draw();

    for(Bullet* bul: _bullets)
        bul->update(deltaTime);
}

void Enemy::shoot()
{
    _bullets.push_back(new Bullet(new Sprite("sprites/enemyBullet.png", {0, 0, 4, 25}), _pos + Vec2(_sizeRect.w/2, _sizeRect.h), false));
}
