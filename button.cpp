#include "button.hpp"

Button::Button(Label* label, GameUtilities* gameUtils):
    _label(label), _gameUtils(gameUtils)
{

}

void Button::update()
{
    _gameUtils->renderText(_label->getTexture(), _label->getRect(), _label->getOffset());
}
