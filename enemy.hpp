#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "globals.hpp"
#include "bullet.hpp"

enum EnemyTypes {Radkata, Sashkata, Kirkata, Genio};

class Enemy
{
public:
    Enemy(EnemyTypes enemyType, Vec2 position);
    ~Enemy();
    void update(float deltaTime);

    void setPosition (Vec2 pos) {_pos = pos;}
    void shoot();
    void die() {_isHit = true;}
    bool isDead() {return _isHit;}

private:
    Sprite* _sprite01;
    SDL_Rect _cropRect01;

    Sprite* _sprite02;
    SDL_Rect _cropRect02;

    SDL_Rect _sizeRect;

    const char* _spriteLocation;
    Vec2 _pos;
    bool _isHit;
    EnemyTypes _enemyType;

    float _spriteTransitionTimer;
    float _spriteTransitionTime;
    bool _isSpriteState01;

    vector<Bullet*> _bullets;
};

#endif
