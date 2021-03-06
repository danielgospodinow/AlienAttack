#include "sdl_components.hpp"

SDL_Window* SDL_Components::_window = NULL;
SDL_Renderer* SDL_Components::_renderer = NULL;
SDL_Event* SDL_Components::_event = NULL;

void SDL_Components::init()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    _window = SDL_CreateWindow("Alien Attack", 100, 100, globals::GAME_WIDTH, globals::GAME_HEIGHT, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    _event = new SDL_Event();

    if (_window == NULL)
    {
        cout << "Widnow failed to create!" << endl;

        killApp();
    }

    SDL_Surface* icon = IMG_Load("sprites/icon.png");
    SDL_SetWindowIcon(_window, icon);
    SDL_FreeSurface(icon);
}

void SDL_Components::close()
{
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    delete _event;
}

void SDL_Components::setVolume(int volPercentage)
{
    Mix_Volume(-1, 128 * volPercentage / 100);
    Mix_VolumeMusic(128 * volPercentage / 100);
}

void SDL_Components::killApp()
{
    exit(0);
}

SDL_Window* const SDL_Components::getWindow()
{
    return _window;
}

SDL_Renderer* const SDL_Components::getRenderer()
{
    return _renderer;
}

SDL_Event* const SDL_Components::getEvent()
{
    return _event;
}
