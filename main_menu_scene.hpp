#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include "scene.hpp"
#include "game_utilities.hpp"

class MainMenuScene : public Scene
{
public:
    MainMenuScene(GameUtilities* gameUtils);
    virtual void update() override;
private:
    GameUtilities* _gameUtils;
};

#endif
