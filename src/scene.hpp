#ifndef SCENE_HPP
#define SCENE_HPP

#include "globals.hpp"
#include "button.hpp"
#include "label.hpp"

class Scene
{
public:
    Scene() {}
    virtual ~Scene() {}
    virtual void update() = 0;
};

#endif
