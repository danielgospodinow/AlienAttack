#ifndef SCENE_HPP
#define SCENE_HPP

#include "globals.hpp"
#include "game_utilities.hpp"

class Scene
{
public:
    explicit Scene(GameUtilities* gameUtils) {_gameUtils = gameUtils;}
    virtual void update() = 0;
protected:
    GameUtilities* _gameUtils;
};

#endif
