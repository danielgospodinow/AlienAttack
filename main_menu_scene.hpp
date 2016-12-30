#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include "scene.hpp"

class MainMenuScene : public Scene
{
public:
    MainMenuScene(GameUtilities* gameUtils);
    virtual ~MainMenuScene() override;
    virtual void update() override;

private:
    Label* _introLabel;
    Label* _creditsLabel;

    Button* _playSPButton;
    Button* _playMPButton;
    Button* _creditialsButton;
};

#endif
