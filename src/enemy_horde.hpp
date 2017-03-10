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
    EnemyHorde(Vec2<int> startPos);
    ~EnemyHorde();
    void update(float deltaTime);
    Vec2<int> getHordeSize() {return _hordeSize;}
    Vec2<int> getHordePos() {return _pos;}
    bool isCollidingWithPlayer(Vec2<int> playerPos);
    bool isABulletColliding(SDL_Rect posnrect);
    vector<Bullet*>* getHordeBullets() {return &_hordeBullets;}

private:
    void initHorde();
    void moveHorde();
    void hordeShoot();
    Vec2<int> getEnemyOffsetInHorde(EnemyTypes type);
    void checkHordeCollision();

    Vec2<int> _pos;
    Vec2<int> _hordeSize;
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
