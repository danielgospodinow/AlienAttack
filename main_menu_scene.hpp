#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP

#include "scene.hpp"

class MainMenuScene : public Scene
{
public:
    using Scene::Scene;
    virtual void update() override;
};

#endif
