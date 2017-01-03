#ifndef PLAYSPSCENE_HPP
#define PLAYSPSCENE_HPP

#include "scene.hpp"
#include "sprite.hpp"
#include "player.hpp"
#include "game.hpp"

class PlaySPScene : public Scene
{
public:
    PlaySPScene(GameUtilities* gameUtils);
    virtual ~PlaySPScene() override;
    virtual void update() override;

private:
    Player* _player;
    bool _isPlayerMovingRight;
    bool _isPlayerMovingLeft;
    bool _isPlayerShooting;

    long _now;
    long _last;
    float _deltaTime;
};

#endif
