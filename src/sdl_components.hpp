#ifndef SDL_COMPONENTS_HPP
#define SDL_COMPONENTS_HPP

#include "globals.hpp"

class SDL_Components
{
public:
    static void init();
    static void close();
    static SDL_Window* const getWindow() {return _window;}
    static SDL_Renderer* const getRenderer() {return _renderer;}
    static SDL_Event* const getEvent() {return _event;}
    static void setVolume(int volPercentage);
    static void killApp() { exit(0); }

private:
    static SDL_Window* _window;
    static SDL_Renderer* _renderer;
    static SDL_Event* _event;
};

#endif
