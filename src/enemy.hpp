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

    void setPosition (Vec2<int> const& pos);

    Vec2<int> getPosition() const;
    SDL_Rect getSize() const;
    EnemyTypes getType() const;

private:
    Sprite* _sprite01;
    SDL_Rect _cropRect01;

    Sprite* _sprite02;
    SDL_Rect _cropRect02;

    SDL_Rect _sizeRect;

    const char* _spriteLocation;
    Vec2<int> _pos;
    EnemyTypes _enemyType;

    float _spriteTransitionTimer;
    float _spriteTransitionTime;
    bool _isSpriteState01;
};

#endif
