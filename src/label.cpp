#include "label.hpp"

Label::Label(const char* text, Vec2 pos, Colors color, int fontSize) :
    _text(text), _textLenght(GameUtilities::getStrLen(text)), _pos(pos), _color(color), _fontSize(fontSize)
{
    (_fontSize>8)?_fontSize=8:_fontSize = _fontSize;

    SDL_Surface* surface = NULL;
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

    surface = TTF_RenderText_Solid(GameUtilities::getFont(), text, fontColor);
    _texture = SDL_CreateTextureFromSurface(SDL_Components::getRenderer(), surface);

    SDL_FreeSurface(surface);

    _rect.w = _textLenght * (globals::LABEL_WIDTH_SCALER * fontSize);
    _rect.h = globals::LABEL_HEIGHT_SCALER * fontSize;
    _rect.x = _pos.x - _rect.w / 2;
    _rect.y = _pos.y - _rect.h / 2;
}

void Label::setText(const char *text)
{
    _textLenght = GameUtilities::getStrLen(text);
    SDL_Surface* surface = NULL;
    SDL_Color fontColor;

    switch(_color)
    {
    case White: fontColor = {255, 255, 255}; break;
    case Black: fontColor = {0, 0, 0}; break;
    case Blue: fontColor = {0, 0, 255}; break;
    case Red: fontColor = {255, 0, 0}; break;
    case Green: fontColor = {0, 255, 0}; break;
    case Yellow: fontColor = {255, 255, 0}; break;
    }

    surface = TTF_RenderText_Solid(GameUtilities::getFont(), text, fontColor);
    _texture = SDL_CreateTextureFromSurface(SDL_Components::getRenderer(), surface);
    SDL_FreeSurface(surface);
    _rect.w = _textLenght * (globals::LABEL_WIDTH_SCALER * _fontSize);
    _rect.h = globals::LABEL_HEIGHT_SCALER * _fontSize;
    _rect.x = _pos.x - _rect.w / 2;
    _rect.y = _pos.y - _rect.h / 2;
}

void Label::changeLabelColor(Colors color)
{
    if(_color == color)
        return;

    SDL_Color fontColor = {0, 0, 0};

    switch(color)
    {
    case White: fontColor = {255, 255, 255}; break;
    case Black: fontColor = {0, 0, 0}; break;
    case Blue: fontColor = {0, 0, 255}; break;
    case Red: fontColor = {255, 0, 0}; break;
    case Green: fontColor = {0, 255, 0}; break;
    case Yellow: fontColor = {255, 255, 0}; break;
    }

    SDL_SetTextureColorMod(_texture, fontColor.r, fontColor.g, fontColor.b);
    _color = color;
}
