#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include "scene.hpp"
#include "game.hpp"
#include "play_sp_scene.hpp"

class MainMenuScene : public Scene
{
public:
    MainMenuScene();
    virtual ~MainMenuScene() override;
    virtual void update() override;

private:
    Label* _introLabel;
    Label* _creditsLabel;

    Button* _playSPButton;
    Button* _playMPButton;
    Button* _creditialsButton;

    Mix_Music* _introMusic;
};

#endif
