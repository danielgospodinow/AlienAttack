#include "button.hpp"
#include "game.hpp"
#include "main_menu_scene.hpp"

Button::Button(Label* label, std::function<void()> func):
    _label(label), _func(func)
{
    _clickedOnce = false;
}

Button::~Button()
{
    delete _label;
}

void Button::update()
{
    Vec2<int> mouseCoords = Vec2<int>(SDL_Components::getEvent()->motion.x, SDL_Components::getEvent()->motion.y);
    bool mouseOnTarget = (mouseCoords.x >= _label->getRect().x + _label->getOffset().x && mouseCoords.x <= _label->getRect().x + _label->getOffset().x + _label->getRect().w) &&
            (mouseCoords.y >= _label->getRect().y + _label->getOffset().y && mouseCoords.y <= _label->getRect().y + _label->getOffset().y + _label->getRect().h);

    if(SDL_Components::getEvent()->type == SDL_MOUSEMOTION)
    {
        if(mouseOnTarget)
            _label->setLabelColor(Colors::Red);
        else
            _label->setLabelColor(Colors::White);
    }
    else if(SDL_Components::getEvent()->type == SDL_MOUSEBUTTONDOWN && !_clickedOnce)
    {
        if(mouseOnTarget)
        {
            _clickedOnce = true;
            _func();
        }
    }
    else if(SDL_Components::getEvent()->type == SDL_MOUSEBUTTONUP)
    {
        _clickedOnce = false;
    }

    GameUtilities::renderText(_label->getTexture(), _label->getRect(), _label->getOffset());
}

Label* Button::getLabel() const {return _label;}
