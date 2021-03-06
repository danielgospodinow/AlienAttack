#include "special_monster.hpp"

SpecialMonster::SpecialMonster(bool leftSpawn):
    _leftSpawn(leftSpawn)
{
    _specialEnemy = new Enemy(EnemyTypes::Genio, Vec2<int>(0, 0));
    _timer = 0;
    _time = GameUtilities::getRandomNumber(3, 7);
    _isSpawned = false;
    _moveTime = 0.005f;
    _moveTimer = 0;
}

SpecialMonster::~SpecialMonster()
{
    delete _specialEnemy;
}

void SpecialMonster::update(float deltaTime)
{
    if(_isDead)
        _isSpawned = false;

    if(!_isSpawned)
    {
        _timer += 1 * deltaTime;

        if(_timer > _time)
        {
            _timer = 0;
            _time = GameUtilities::getRandomNumber(5, 10);
            _leftSpawn = GameUtilities::getRandomNumber(0,1);

            if(_leftSpawn)
                _pos = Vec2<int>(0 - _specialEnemy->getSize().w, 10);
            else
                _pos = Vec2<int>(globals::GAME_WIDTH, 10);

            _isSpawned = true;
            _isDead = false;
        }

        return;
    }

    if(_pos.x > globals::GAME_WIDTH || _pos.x < 0 - _specialEnemy->getSize().w)
    {
        _isDead = true;
        return;
    }

    _moveTimer += 1 * deltaTime;

    if(_leftSpawn && _moveTimer > _moveTime)
    {
        _moveTimer = 0;
        _pos = _pos + Vec2<int>(1, 0);
        _specialEnemy->setPosition(_pos);
    }
    else if (!_leftSpawn && _moveTimer > _moveTime)
    {
        _moveTimer = 0;
        _pos = _pos + Vec2<int>(-1, 0);
        _specialEnemy->setPosition(_pos);
    }

    _specialEnemy->update(deltaTime);
}

void SpecialMonster::kill()
{
     _isDead = true;
}

bool SpecialMonster::isDead() const
{
    return _isDead;
}

SDL_Rect SpecialMonster::getSize() const
{
    return _specialEnemy->getSize();
}
