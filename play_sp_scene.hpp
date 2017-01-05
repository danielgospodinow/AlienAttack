#ifndef PLAYSPSCENE_HPP
#define PLAYSPSCENE_HPP

#include "scene.hpp"
#include "sprite.hpp"
#include "player.hpp"
#include "game.hpp"
#include "enemy_horde.hpp"
#include "special_monster.hpp"

class PlaySPScene : public Scene
{
public:
    PlaySPScene(GameUtilities* gameUtils);
    virtual ~PlaySPScene() override;
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
    bool handleDeadPlayer();
    void handleSpecialEnemy();

    Player* _player;
    bool _isPlayerMovingRight;
    bool _isPlayerMovingLeft;
    bool _isPlayerShooting;

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
};

#endif
