#ifndef BULLET_HPP
#define BULLET_HPP

#include "globals.hpp"
#include "sprite.hpp"

class Bullet
{
public:
    Bullet(Sprite* sprite, Vec2 pos, bool travelUp = true);
    ~Bullet();
    void update(float deltaTime);
    bool isDestroyed() {return _isDestroyed;}
    void destroy() {_isDestroyed = true;}
    void setPosition(Vec2 pos);
    Sprite* getSprite() {return _sprite;}

private:
    Sprite* _sprite;
    Vec2 _pos;
    bool _isDestroyed;
    bool _travelUp;
    float _moveTime;
    float _moveTimer;
};

#endif
