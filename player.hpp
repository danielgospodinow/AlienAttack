#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "globals.hpp"
#include "sprite.hpp"
#include "bullet.hpp"

class Player
{
public:
    Player(Sprite* sprite, Vec2 pos);
    ~Player();

    Sprite* getSprite() {return _sprite;}
    Vec2 getPosition() {return _pos;}

    void setPosition(Vec2 pos) {_pos = pos; _sprite->setPosition(pos);}

    void moveRight(float deltaTime);
    void moveLeft(float deltaTime);

    void shoot();

    void drawAndUpdate(float deltaTime);

private:
    Sprite* _sprite;
    Vec2 _pos;
    std::vector<Bullet*> _bullets;
    float _shootDelay;
    float _shootDelayTimer;
};

#endif
