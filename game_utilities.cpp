#include "game_utilities.hpp"

GameUtilities::GameUtilities(SDL_Components* sdlComponents)
{
    _sdlComponents = sdlComponents;

    _font = TTF_OpenFont("fonts/raidercrusader.ttf", 24);
    _surfaceMessage = NULL;
    _message = NULL;
}

void GameUtilities::printText(const char *text, Colors color, Vec2 textLocation, Vec2 textSize)
{
    SDL_Color fontColor;
    SDL_Rect rect = {textLocation.x, textLocation.y, textSize.x, textSize.y};

    switch(color)
    {
    case White: fontColor = {255, 255, 255}; break;
    case Black: fontColor = {0, 0, 0}; break;
    case Blue: fontColor = {0, 0, 255}; break;
    case Red: fontColor = {255, 0, 0}; break;
    case Green: fontColor = {0, 255, 0}; break;
    case Yellow: fontColor = {255, 255, 0}; break;
    }

    _surfaceMessage = TTF_RenderText_Solid(_font, text, fontColor);
    _message = SDL_CreateTextureFromSurface(_sdlComponents->getRenderer(), _surfaceMessage);

    SDL_RenderCopy(_sdlComponents->getRenderer(), _message, NULL, &rect);

    SDL_FreeSurface(_surfaceMessage);
    SDL_DestroyTexture(_message);
}

SDL_Texture* GameUtilities::getText(const char *text, Colors color)
{
    SDL_Color fontColor;

    switch(color)
    {
    case White: fontColor = {255, 255, 255}; break;
    case Black: fontColor = {0, 0, 0}; break;
    case Blue: fontColor = {0, 0, 255}; break;
    case Red: fontColor = {255, 0, 0}; break;
    case Green: fontColor = {0, 255, 0}; break;
    case Yellow: fontColor = {255, 255, 0}; break;
    }

    _surfaceMessage = TTF_RenderText_Solid(_font, text, fontColor);
    _message = SDL_CreateTextureFromSurface(_sdlComponents->getRenderer(), _surfaceMessage);

    SDL_FreeSurface(_surfaceMessage);
    return _message;
}

void GameUtilities::renderText(SDL_Texture* texture, Vec2 pos, Vec2 size)
{
    SDL_Rect rect = {pos.x, pos.y, size.x, size.y};
    SDL_RenderCopy(_sdlComponents->getRenderer(), texture, NULL, &rect);
}
