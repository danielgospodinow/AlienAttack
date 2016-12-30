#ifndef SCENE_HPP
#define SCENE_HPP

#include "globals.hpp"
#include "button.hpp"
#include "label.hpp"

class Scene
{
public:
    Scene(GameUtilities* gameUtils) {_gameUtils = gameUtils;}
    virtual ~Scene() {delete _gameUtils;}
    virtual void update() = 0;
protected:
    GameUtilities* _gameUtils;
};

#endif
