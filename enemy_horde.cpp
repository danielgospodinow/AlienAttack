#include "enemy_horde.hpp"

EnemyHorde::EnemyHorde(Vec2 startPos):
    _pos(startPos)
{
    _maxUnitWidth = 38;
    _unitWDistance = _maxUnitWidth + 6;
    _unitHDistance = 32;
    _hordeSize = Vec2(globals::ENEMY_HORDE_WIDTH * _unitWDistance, globals::ENEMY_HORDE_HEIGHT * _unitHDistance);
    _isHordeMovingRight = true;

    _moveTimer = 0;
    _moveTime = 2;

    _shootTimer = 0;
    _shootTime = 4;

    initHorde();
}

EnemyHorde::~EnemyHorde()
{
    for(int i=0; i<globals::ENEMY_HORDE_HEIGHT; i++)
    {
        for(int j=0; j<globals::ENEMY_HORDE_WIDTH; j++)
        {
            Enemy* currentEnemy = _enemyHorde[i][j];
            if(currentEnemy)
                delete currentEnemy;
        }
    }
}

void EnemyHorde::initHorde()
{
    for(int i=0; i<globals::ENEMY_HORDE_HEIGHT; i++)
    {
        for(int j=0; j<globals::ENEMY_HORDE_WIDTH; j++)
        {
            if(i <= globals::ENEMY_HORDE_HEIGHT / 2 - 1)
                _enemyHorde[i][j] = new Enemy(EnemyTypes::Radkata, _pos + Vec2(j * _unitWDistance, i * _unitHDistance) + getEnemyOffsetInHorde(Radkata));

            else if(i > globals::ENEMY_HORDE_HEIGHT / 2 - 1 && i <= globals::ENEMY_HORDE_HEIGHT / 2 + 1)
                _enemyHorde[i][j] = new Enemy(EnemyTypes::Sashkata, _pos + Vec2(j * _unitWDistance, i * _unitHDistance) + getEnemyOffsetInHorde(Sashkata));

            else
                _enemyHorde[i][j] = new Enemy(EnemyTypes::Kirkata, _pos + Vec2(j * _unitWDistance, i * _unitHDistance) + getEnemyOffsetInHorde(Kirkata));
        }
    }
}

void EnemyHorde::update(float deltaTime)
{
    _moveTimer += 1 * deltaTime;
    _shootTimer += 1 * deltaTime;

    if(_moveTimer > _moveTime)
    {
        _moveTimer = 0;
        moveHorde();
    }
    if(_shootTimer > _shootTime)
    {
        hordeShoot();
        _shootTime = GameUtilities::getRandomNumber(1, 6);
        _shootTimer = 0;
    }

    Enemy* currentEnemy = NULL;

    for(int i=0; i<globals::ENEMY_HORDE_HEIGHT; i++)
    {
        for(int j=0; j<globals::ENEMY_HORDE_WIDTH; j++)
        {
            currentEnemy = _enemyHorde[i][j];

            if(!currentEnemy)
                continue;

            if(currentEnemy->isDead())
            {
                delete currentEnemy;
                currentEnemy = NULL;
            }

            currentEnemy->update(deltaTime);
        }
    }
}

void EnemyHorde::moveHorde()
{
    int moveStep = (globals::GAME_WIDTH - _hordeSize.x) / 10;

    if(_isHordeMovingRight)
    {
        if(_pos.x + _hordeSize.x + moveStep > globals::GAME_WIDTH)
        {
            _isHordeMovingRight = ! _isHordeMovingRight;
            _pos.y += _unitHDistance;
            return;
        }

        _pos = _pos + Vec2(moveStep, 0);
    }
    else
    {
        if(_pos.x - moveStep < 0)
        {
            _isHordeMovingRight = ! _isHordeMovingRight;
            _pos.y += _unitHDistance;
            return;
        }

        _pos = _pos - Vec2(moveStep, 0);
    }

    for(int i=0; i<globals::ENEMY_HORDE_HEIGHT; i++)
    {
        for(int j=0; j<globals::ENEMY_HORDE_WIDTH; j++)
        {
            if(i <= globals::ENEMY_HORDE_HEIGHT / 2 - 1)
                _enemyHorde[i][j]->setPosition(_pos + Vec2(j * _unitWDistance, i * _unitHDistance) + getEnemyOffsetInHorde(Radkata));

            else if(i > globals::ENEMY_HORDE_HEIGHT / 2 - 1 && i <= globals::ENEMY_HORDE_HEIGHT / 2 + 1)
                _enemyHorde[i][j]->setPosition(_pos + Vec2(j * _unitWDistance, i * _unitHDistance) + getEnemyOffsetInHorde(Sashkata));

            else
                _enemyHorde[i][j]->setPosition(_pos + Vec2(j * _unitWDistance, i * _unitHDistance) + getEnemyOffsetInHorde(Kirkata));
        }
    }
}

void EnemyHorde::hordeShoot()
{
    for(int i=globals::ENEMY_HORDE_HEIGHT - 1; i>=0; i--)
    {
        vector<int> avaivableShooters;

        for(int j=0; j<globals::ENEMY_HORDE_WIDTH; j++)
        {
            if(!_enemyHorde[i][j])
                continue;

            avaivableShooters.push_back(j);
        }

        if(avaivableShooters.size() == 0)
            continue;

        int shooterIndex = avaivableShooters.at(GameUtilities::getRandomNumber(0, avaivableShooters.size() - 1));
        _enemyHorde[i][shooterIndex]->shoot();
        break;
    }
}

Vec2 EnemyHorde::getEnemyOffsetInHorde(EnemyTypes type)
{
    Vec2 offset = Vec2(0,0);

    switch (type)
    {
    case Radkata: offset.x = 6; break;
    case Sashkata: offset.x = 1; break;
    case Kirkata: offset.x = 0; break;
    case Genio: break;
    }

    return offset;
}
