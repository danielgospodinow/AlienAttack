#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP

#include "scene.hpp"
#include "sprite.hpp"
#include "player.hpp"
#include "game.hpp"
#include "enemy_horde.hpp"
#include "special_monster.hpp"
#include "health_bar.h"
#include "barricades.hpp"
#include "ui.hpp"

class PlayScene: public Scene
{
public:
    PlayScene();
    virtual ~PlayScene() override;
    virtual void update();

protected:
    void handleDeltaTime();
    virtual bool handleInput();
    virtual void clearPlayScene();
    void handleBarricades();
    virtual void handleUpdating();
    void handlePlayer();
    virtual bool handleDeadPlayer();
    bool handleDeadHorde();
    void handleSpecialEnemy();

    UI* _ui;
    Label* _youLoseLabel;
    Label* _youWinLabel;
    EnemyHorde* _enemyHorde;
    SpecialMonster* _specialEnemy;
    Mix_Music* _introMusic;
    Barricades* _barricades;

    Player* _player;
    bool _isPlayerMovingRight;
    bool _isPlayerMovingLeft;
    bool _isPlayerShooting;

    long _now;
    long _last;
    float _deltaTime;

    int _lastScore;
};

#endif
