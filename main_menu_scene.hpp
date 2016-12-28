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
    SDL_Texture* _introLabel;
    Vec2 _introTextSize;
    Vec2 _introTextPos;
    SDL_Texture* _creditsLabel;
    Vec2 _creditsTextSize;
    Vec2 _creditsTextPos;
};

#endif
