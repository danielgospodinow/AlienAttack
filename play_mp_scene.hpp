#ifndef PLAYMPSCENE_HPP
#define PLAYMPSCENE_HPP

#include "scene.hpp"
#include "player.hpp"
#include "game.hpp"
#include "enemy_horde.hpp"
#include "special_monster.hpp"
#include "health_bar.h"

class PlayMPScene : public Scene
{
public:
    PlayMPScene();
    virtual ~PlayMPScene() override;
    virtual void update() override;

    static int getScore() {return _score;}
    static void setScore(int score) {_score = score; _labelUpToDate = false;}

private:
    void handleDeltaTime();
    bool handleInput();
    void clearPlayScene();
    void handleBarricades();
    void handleUpdating();
    void handlePlayer();
    void handlePlayerTwo();
    bool handleDeadPlayer();
    void handleSpecialEnemy();

    Player* _player;
    bool _isPlayerMovingRight;
    bool _isPlayerMovingLeft;
    bool _isPlayerShooting;

    Player* _playerTwo;
    bool _isPlayerTwoMovingRight;
    bool _isPlayerTwoMovingLeft;
    bool _isPlayerTwoShooting;

    long _now;
    long _last;
    float _deltaTime;

    EnemyHorde* _enemyHorde;
    Label* _youLoseLabel;
    Sprite* _barricads[globals::BARRICADES_SIZE];

    SpecialMonster* _specialEnemy;

    static int _score;
    Label* _scoreTextLabel;
    Label* _scoreNumLabel;
    static bool _labelUpToDate;

    Mix_Music* _introMusic;

    HealthBar* _healthBar;
    HealthBar* _healthBarTwo;
};

#endif