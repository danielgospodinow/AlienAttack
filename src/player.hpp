#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "globals.hpp"
#include "sprite.hpp"
#include "bullet.hpp"

class Player
{
public:
    Player(Sprite* sprite, Vec2<int> pos);
    ~Player();

    Sprite* getSprite() const;
    Vec2<int> getPosition() const;
    bool isAlive() const;

    void setPosition(Vec2<int> pos);

    void moveRight();
    void moveLeft();

    void shoot();

    void drawAndUpdate(float deltaTime);

    static std::vector<Bullet*> getBullets();

    void kill();

private:
    static std::vector<Bullet*> _bullets;
    Sprite* _sprite;
    Vec2<int> _pos;
    float _shootDelay;
    float _shootDelayTimer;
    bool _isAlive;
    Mix_Chunk* _shootSound;
    float _moveTimer;
    float _moveTime;
};

#endif
