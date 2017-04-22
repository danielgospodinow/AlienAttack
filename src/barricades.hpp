#ifndef BARRICADES_HPP
#define BARRICADES_HPP

#include "globals.hpp"
#include "enemy_horde.hpp"
#include "bullet.hpp"
#include "sprite.hpp"

class Barricades
{
public:
    Barricades(Vec2<int> playerPos);
    ~Barricades();

    void handle(EnemyHorde* enemyHorde);
    void draw();

private:
    Sprite* _barricads[globals::BARRICADES_SIZE];
};

#endif
