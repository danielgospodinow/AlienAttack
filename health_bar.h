#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP

#include "globals.hpp"
#include "sprite.hpp"

class HealthBar
{
public:
    HealthBar(int lives);
    ~HealthBar();
    void update();
    void reduce();
    int getLives() {return _lives;}

private:
    Sprite* _healthBar;
    Vec2 _pos;
    int _lives;
};

#endif
