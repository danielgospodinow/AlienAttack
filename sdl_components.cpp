#include "sdl_components.hpp"

SDL_Components::SDL_Components()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();

    _window = SDL_CreateWindow("Alien Attack", 100, 100, globals::GAME_WIDTH, globals::GAME_HEIGHT, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    _event = new SDL_Event();

    if (_window == NULL)
    {
        cout << "Widnow failed to create!" << endl;

        SDL_Quit();
        exit(0);
    }
}

SDL_Components::~SDL_Components()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    delete _event;
}
