#ifndef PLAYSPSCENE_HPP
#define PLAYSPSCENE_HPP

#include "play_scene.hpp"

class PlaySPScene : public PlayScene
{
public:
    PlaySPScene();
    virtual ~PlaySPScene() override;
    virtual void update() override;
};

#endif
