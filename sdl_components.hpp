#ifndef SDL_COMPONENTS_HPP
#define SDL_COMPONENTS_HPP

#include "globals.hpp"

class SDL_Components
{
public:
    SDL_Components();
    ~SDL_Components();

    SDL_Window* getWindow() {return _window;}
    SDL_Renderer* getRenderer() {return _renderer;}
    SDL_Event* getEvent() {return _event;}
    static void killApp() { TTF_Quit(); SDL_Quit(); exit(0); }

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    SDL_Event* _event;
};

#endif
