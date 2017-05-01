#ifndef HIGHSCORES_SCENE
#define HIGHSCORES_SCENE

#include "game.hpp"
#include "scene.hpp"

class HighscoreScene : public Scene
{
public:
    HighscoreScene();
    virtual ~HighscoreScene() override;
    virtual void update() override;

private:
    void handleInput();
    void clearScene();

    Label* _labels[globals::MAX_HIGHSCORES];
};

#endif
