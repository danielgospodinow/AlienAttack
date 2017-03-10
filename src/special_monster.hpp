#ifndef SPECIALMONSTER_HPP
#define SPECIALMONSTER_HPP

#include "globals.hpp"
#include "enemy.hpp"
#include "game_utilities.hpp"

class SpecialMonster
{
public:
    SpecialMonster(bool leftSpawn);
    ~SpecialMonster() {delete _specialEnemy;}
    SDL_Rect getSize() {return _specialEnemy->getSize();}
    void update(float deltaTime);
    bool isDead() {return _isDead;}
    void kill () {_isDead = true;}

private:
    Enemy* _specialEnemy;
    Vec2<int> _pos;
    float _timer;
    float _time;
    bool _isSpawned;
    bool _leftSpawn;
    bool _isDead;
    float _moveTimer;
    float _moveTime;
};

#endif
