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

    void moveRight();
    void moveLeft();

    void shoot();

    void drawAndUpdate(float deltaTime);

    static std::vector<Bullet*> getBullets() {return _bullets;}

    void kill() {_isAlive = false;}
    bool isAlive() {return _isAlive;}

private:
    static std::vector<Bullet*> _bullets;
    Sprite* _sprite;
    Vec2 _pos;
    float _shootDelay;
    float _shootDelayTimer;
    bool _isAlive;
    Mix_Chunk* _shootSound;
    float _moveTimer;
    float _moveTime;
};

#endif
