#include "enemy_horde.hpp"
#include "play_sp_scene.hpp"
#include "play_mp_scene.hpp"

EnemyHorde::EnemyHorde(Vec2<int> startPos):
    _pos(startPos)
{
    _maxUnitWidth = 38;
    _unitWDistance = _maxUnitWidth + 6;
    _unitHDistance = 32;
    _hordeSize = Vec2<int>(globals::ENEMY_HORDE_WIDTH * _unitWDistance, globals::ENEMY_HORDE_HEIGHT * _unitHDistance);
    _isHordeMovingRight = true;

    _moveTimer = 0;
    _moveTime = 2;

    _shootTimer = 0;
    _shootTime = 4;

    initHorde();

    _shootSound = Mix_LoadWAV("sounds/enemyShoot.wav");
    _deadEnemySound = Mix_LoadWAV("sounds/deadEnemy.wav");
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

    for(Uint32 i=0; i<_hordeBullets.size(); i++)
    {
        Bullet* bul = _hordeBullets.at(i);
        if(bul)
            delete bul;
    }

    Mix_FreeChunk(_shootSound);
    Mix_FreeChunk(_deadEnemySound);
}

void EnemyHorde::update(float deltaTime)
{
    _moveTimer += 1 * deltaTime;
    _shootTimer += 1 * deltaTime;

    if(_shootTimer > _shootTime)
    {
        hordeShoot();
        _shootTime = GameUtilities::getRandomNumber(1, 6);
        _shootTimer = 0;
    }
    if(_moveTimer > _moveTime)
    {
        _moveTimer = 0;
        moveHorde();
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
                _enemyHorde[i][j] = NULL;
                continue;
            }

            currentEnemy->update(deltaTime);
        }
    }

    for(Uint32 i=0; i<_hordeBullets.size(); i++)
    {
        Bullet* bul = _hordeBullets.at(i);
        bul->update(deltaTime);
    }

    checkHordeCollision();
}


void EnemyHorde::initHorde()
{
    for(int i=0; i<globals::ENEMY_HORDE_HEIGHT; i++)
    {
        for(int j=0; j<globals::ENEMY_HORDE_WIDTH; j++)
        {
            if(i <= globals::ENEMY_HORDE_HEIGHT / 2 - 1)
                _enemyHorde[i][j] = new Enemy(EnemyTypes::Radkata, _pos + Vec2<int>(j * _unitWDistance, i * _unitHDistance) + getEnemyOffsetInHorde(Radkata));

            else if(i > globals::ENEMY_HORDE_HEIGHT / 2 - 1 && i <= globals::ENEMY_HORDE_HEIGHT / 2 + 1)
                _enemyHorde[i][j] = new Enemy(EnemyTypes::Sashkata, _pos + Vec2<int>(j * _unitWDistance, i * _unitHDistance) + getEnemyOffsetInHorde(Sashkata));

            else
                _enemyHorde[i][j] = new Enemy(EnemyTypes::Kirkata, _pos + Vec2<int>(j * _unitWDistance, i * _unitHDistance) + getEnemyOffsetInHorde(Kirkata));
        }
    }
}

void EnemyHorde::checkHordeCollision()
{
    std::vector<Bullet*> playerBullets = Player::getBullets();

    for(int i=0; i<globals::ENEMY_HORDE_HEIGHT; i++)
    {
        for(int j=0; j<globals::ENEMY_HORDE_WIDTH; j++)
        {
            if(!_enemyHorde[i][j])
                continue;

            for(Uint32 k=0; k<playerBullets.size(); k++)
            {
                Bullet* playerBullet = playerBullets.at(k);

                if(GameUtilities::areColliding(_enemyHorde[i][j]->getSize(), playerBullet->getSprite()->getPosnsizeRect()))
                {
                    switch (_enemyHorde[i][j]->getType())
                    {
                    case Radkata: GameUtilities::setScore(GameUtilities::getScore() + 30);
                    case Sashkata: GameUtilities::setScore(GameUtilities::getScore() + 20);
                    case Kirkata: GameUtilities::setScore(GameUtilities::getScore() + 10);
                    case Genio: break;
                    }

                    Mix_PlayChannel(-1, _deadEnemySound, 0);
                    _enemyHorde[i][j]->die();
                    playerBullet->destroy();
                }
            }
        }
    }
}

bool EnemyHorde::isCollidingWithPlayer(Vec2<int> playerPos)
{
    for(int i=0; i<globals::ENEMY_HORDE_HEIGHT; i++)
    {
        for(int j=0; j<globals::ENEMY_HORDE_WIDTH; j++)
        {
            if(!_enemyHorde[i][j])
                continue;

            if(GameUtilities::areColliding(_enemyHorde[i][j]->getSize(), {playerPos.x, playerPos.y, globals::PLAYER_SPRITE_SIZE_X, globals::PLAYER_SPRITE_SIZE_Y}))
                return true;
        }
    }

    return false;
}

bool EnemyHorde::isABulletColliding(SDL_Rect posnrect)
{
    Bullet* currentBullet = NULL;

    for(Uint32 i=0; i<_hordeBullets.size(); i++)
    {
        currentBullet = _hordeBullets.at(i);
        if(GameUtilities::areColliding(currentBullet->getSprite()->getPosnsizeRect(), {posnrect.x, posnrect.y, posnrect.w, posnrect.h}))
        {
            _hordeBullets.erase(std::remove(_hordeBullets.begin(), _hordeBullets.end(), currentBullet), _hordeBullets.end());
            delete currentBullet;
            return true;
        }
    }

    return false;
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

        _pos = _pos + Vec2<int>(moveStep, 0);
    }
    else
    {
        if(_pos.x - moveStep < 0)
        {
            _isHordeMovingRight = ! _isHordeMovingRight;
            _pos.y += _unitHDistance;
            return;
        }

        _pos = _pos - Vec2<int>(moveStep, 0);
    }

    for(int i=0; i<globals::ENEMY_HORDE_HEIGHT; i++)
    {
        for(int j=0; j<globals::ENEMY_HORDE_WIDTH; j++)
        {
            if(!_enemyHorde[i][j])
                continue;

            if(i <= globals::ENEMY_HORDE_HEIGHT / 2 - 1)
                _enemyHorde[i][j]->setPosition(_pos + Vec2<int>(j * _unitWDistance, i * _unitHDistance) + getEnemyOffsetInHorde(Radkata));

            else if(i > globals::ENEMY_HORDE_HEIGHT / 2 - 1 && i <= globals::ENEMY_HORDE_HEIGHT / 2 + 1)
                _enemyHorde[i][j]->setPosition(_pos + Vec2<int>(j * _unitWDistance, i * _unitHDistance) + getEnemyOffsetInHorde(Sashkata));

            else
                _enemyHorde[i][j]->setPosition(_pos + Vec2<int>(j * _unitWDistance, i * _unitHDistance) + getEnemyOffsetInHorde(Kirkata));
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
            if(!_enemyHorde[i][j] || (i < globals::ENEMY_HORDE_HEIGHT - 1 && _enemyHorde[i + 1][j]))
                continue;

            avaivableShooters.push_back(j);
        }

        if(avaivableShooters.size() == 0)
            continue;

        Mix_PlayChannel(-1, _shootSound, 0);
        int shooterIndex = avaivableShooters.at(GameUtilities::getRandomNumber(0, avaivableShooters.size() - 1));
        _hordeBullets.push_back(new Bullet(new Sprite("sprites/enemyBullet.png", {0, 0, 4, 25}), _enemyHorde[i][shooterIndex]->getPosition() + Vec2<int>(_enemyHorde[i][shooterIndex]->getSize().w/2, _enemyHorde[i][shooterIndex]->getSize().h), false));
    }
}

Vec2<int> EnemyHorde::getEnemyOffsetInHorde(EnemyTypes type)
{
    Vec2<int> offset = Vec2<int>(0,0);

    switch (type)
    {
    case Radkata: offset.x = 6; break;
    case Sashkata: offset.x = 1; break;
    case Kirkata: offset.x = 0; break;
    case Genio: break;
    }

    return offset;
}
