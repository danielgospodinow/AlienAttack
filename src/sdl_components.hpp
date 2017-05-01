#ifndef SDL_COMPONENTS_HPP
#define SDL_COMPONENTS_HPP

#include "globals.hpp"

class SDL_Components
{
public:
    static void init();
    static void close();

    static SDL_Window* const getWindow();
    static SDL_Renderer* const getRenderer();
    static SDL_Event* const getEvent();

    static void setVolume(int volPercentage);
    static void killApp();

private:
    SDL_Components() {}

    static SDL_Window* _window;
    static SDL_Renderer* _renderer;
    static SDL_Event* _event;
};

#endif
