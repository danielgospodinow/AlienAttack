#ifndef BULLET_HPP
#define BULLET_HPP

#include "globals.hpp"
#include "sprite.hpp"

class Bullet
{
public:
    Bullet(Sprite* sprite, Vec2<int> pos, bool travelUp = true);
    ~Bullet();

    void update(float deltaTime);

    bool isDestroyed() const;
    Sprite* getSprite() const;

    void destroy();
    void setPosition(Vec2<int> pos);

private:
    Sprite* _sprite;
    Vec2<int> _pos;
    bool _isDestroyed;
    bool _travelUp;
    float _moveTime;
    float _moveTimer;
};

#endif
