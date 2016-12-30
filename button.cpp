#include "button.hpp"

Button::Button(Label* label, GameUtilities* gameUtils, std::function<void()> func):
    _label(label), _gameUtils(gameUtils), _func(func)
{

}

void Button::update()
{
    _gameUtils->renderText(_label->getTexture(), _label->getRect(), _label->getOffset());

    _func();
}
