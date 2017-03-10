#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "globals.hpp"
#include "sprite.hpp"

enum EnemyTypes {Radkata, Sashkata, Kirkata, Genio};

class Enemy
{
public:
    Enemy(EnemyTypes enemyType, Vec2<int> position);
    ~Enemy();
    void update(float deltaTime);

    void setPosition (Vec2<int> pos) {_pos = pos; _sizeRect.x = pos.x; _sizeRect.y = pos.y;}
    Vec2<int> getPosition() {return _pos;}
    SDL_Rect getSize() {return _sizeRect;}
    void die() {_isHit = true; }
    bool isDead() {return _isHit;}
    EnemyTypes getType() {return _enemyType;}

private:
    Sprite* _sprite01;
    SDL_Rect _cropRect01;

    Sprite* _sprite02;
    SDL_Rect _cropRect02;

    SDL_Rect _sizeRect;

    const char* _spriteLocation;
    Vec2<int> _pos;
    bool _isHit;
    EnemyTypes _enemyType;

    float _spriteTransitionTimer;
    float _spriteTransitionTime;
    bool _isSpriteState01;
};

#endif
