#include "button.hpp"

Button::Button(Label* label, GameUtilities* gameUtils, std::function<void()> func):
    _label(label), _gameUtils(gameUtils), _func(func)
{
    _clickedOnce = false;
}

void Button::update()
{
    _mouseCoords = Vec2(SDL_Components::getEvent()->motion.x, SDL_Components::getEvent()->motion.y);

    if(SDL_Components::getEvent()->type == SDL_MOUSEMOTION)
    {
        if((_mouseCoords.x >= _label->getRect().x + _label->getOffset().x && _mouseCoords.x <= _label->getRect().x + _label->getOffset().x + _label->getRect().w) &&
                (_mouseCoords.y >= _label->getRect().y + _label->getOffset().y && _mouseCoords.y <= _label->getRect().y + _label->getOffset().y + _label->getRect().h))
            _label->changeLabelColor(Colors::Red);
        else
            _label->changeLabelColor(Colors::White);
    }
    else if(SDL_Components::getEvent()->type == SDL_MOUSEBUTTONDOWN && !_clickedOnce)
    {
        _mouseCoords = Vec2(SDL_Components::getEvent()->motion.x, SDL_Components::getEvent()->motion.y);

        if((_mouseCoords.x >= _label->getRect().x + _label->getOffset().x && _mouseCoords.x <= _label->getRect().x + _label->getOffset().x + _label->getRect().w) &&
                (_mouseCoords.y >= _label->getRect().y + _label->getOffset().y && _mouseCoords.y <= _label->getRect().y + _label->getOffset().y + _label->getRect().h))
        {
            _clickedOnce = true;
            _func();
        }
    }
    else if(SDL_Components::getEvent()->type == SDL_MOUSEBUTTONUP)
    {
        _clickedOnce = false;
    }

    _gameUtils->renderText(_label->getTexture(), _label->getRect(), _label->getOffset());
}
