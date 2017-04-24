#ifndef PLAYSPSCENE_HPP
#define PLAYSPSCENE_HPP

#include "scene.hpp"
#include "sprite.hpp"
#include "player.hpp"
#include "game.hpp"
#include "enemy_horde.hpp"
#include "special_monster.hpp"
#include "health_bar.h"
#include "barricades.hpp"
#include "ui.hpp"

class PlaySPScene : public Scene
{
public:
    PlaySPScene();
    virtual ~PlaySPScene() override;
    virtual void update() override;

private:
    void handleDeltaTime();
    bool handleInput();
    void clearPlayScene();
    void handleBarricades();
    void handleUpdating();
    void handlePlayer();
    bool handleDeadPlayer();
    bool handleDeadHorde();
    void handleSpecialEnemy();

    UI* _ui;
    Label* _youLoseLabel;
    Label* _youWinLabel;
    EnemyHorde* _enemyHorde;
    SpecialMonster* _specialEnemy;
    Mix_Music* _introMusic;
    HealthBar* _healthBar;
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
