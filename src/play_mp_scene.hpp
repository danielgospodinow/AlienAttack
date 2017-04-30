#ifndef PLAYMPSCENE_HPP
#define PLAYMPSCENE_HPP

#include "play_scene.hpp"

class PlayMPScene : public PlayScene
{
public:
    PlayMPScene();
    virtual ~PlayMPScene() override;
    virtual void update() override;

private:
    virtual bool handleInput() override;
    virtual void clearPlayScene() override;
    virtual void handleUpdating() override;
    virtual bool handleDeadPlayer() override;
    void handlePlayerTwo();

    Player* _playerTwo;
    bool _isPlayerTwoMovingRight;
    bool _isPlayerTwoMovingLeft;
    bool _isPlayerTwoShooting;
    bool _isPlayerTwoAI;
    bool _playerTwoAIRight;
    float _playerTwoAITimer;
};

#endif
