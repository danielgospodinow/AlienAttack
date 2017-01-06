#ifndef ENEMYHORDE_HPP
#define ENEMYHORDE_HPP

#include "globals.hpp"
#include "enemy.hpp"
#include "game_utilities.hpp"
#include "bullet.hpp"
#include "player.hpp"

class EnemyHorde
{
public:
    EnemyHorde(Vec2 startPos);
    ~EnemyHorde();
    void update(float deltaTime);
    Vec2 getHordeSize() {return _hordeSize;}
    Vec2 getHordePos() {return _pos;}
    bool isCollidingWithPlayer(Vec2 playerPos);
    bool isABulletColliding(SDL_Rect posnrect);

private:
    void initHorde();
    void moveHorde();
    void hordeShoot();
    Vec2 getEnemyOffsetInHorde(EnemyTypes type);
    void checkHordeCollision();

    Vec2 _pos;
    Vec2 _hordeSize;
    Enemy* _enemyHorde [globals::ENEMY_HORDE_HEIGHT][globals::ENEMY_HORDE_WIDTH];
    vector<Bullet*> _hordeBullets;
    int _maxUnitWidth;
    int _unitWDistance;
    int _unitHDistance;

    bool _isHordeMovingRight;
    float _moveTimer;
    float _moveTime;

    float _shootTimer;
    float _shootTime;

    Mix_Chunk* _shootSound;
    Mix_Chunk* _deadEnemySound;
};

#endif
