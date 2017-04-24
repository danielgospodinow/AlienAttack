#ifndef PLAYMPSCENE_HPP
#define PLAYMPSCENE_HPP

#include "scene.hpp"
#include "player.hpp"
#include "game.hpp"
#include "enemy_horde.hpp"
#include "special_monster.hpp"
#include "health_bar.h"
#include "barricades.hpp"
#include "ui.hpp"

class PlayMPScene : public Scene
{
public:
    PlayMPScene();
    virtual ~PlayMPScene() override;
    virtual void update() override;

private:
    void handleDeltaTime();
    bool handleInput();
    void clearPlayScene();
    void handleBarricades();
    void handleUpdating();
    void handlePlayer();
    void handlePlayerTwo();
    bool handleDeadPlayer();
    bool handleDeadHorde();
    void handleSpecialEnemy();

    Player* _player;
    bool _isPlayerMovingRight;
    bool _isPlayerMovingLeft;
    bool _isPlayerShooting;

    Player* _playerTwo;
    bool _isPlayerTwoMovingRight;
    bool _isPlayerTwoMovingLeft;
    bool _isPlayerTwoShooting;
    bool _isPlayerTwoAI;
    bool _playerTwoAIRight;
    float _playerTwoAITimer;

    long _now;
    long _last;
    float _deltaTime;

    int _lastScore;

    UI* _ui;
    EnemyHorde* _enemyHorde;
    SpecialMonster* _specialEnemy;
    Barricades* _barricades;
    Mix_Music* _introMusic;
    Label* _youLoseLabel;
    Label* _youWinLabel;
};

#endif
