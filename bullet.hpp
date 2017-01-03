#ifndef BULLET_HPP
#define BULLET_HPP

#include "globals.hpp"
#include "sprite.hpp"

class Bullet
{
public:
    Bullet(Sprite* sprite, Vec2 pos);
    ~Bullet();
    void update(float deltaTime);
    bool isDestroyed() {return _isDestroyed;}
    void setPosition(Vec2 pos);
    Sprite* getSprite() {return _sprite;}

private:
    Sprite* _sprite;
    Vec2 _pos;
    bool _isDestroyed;
};

#endif
