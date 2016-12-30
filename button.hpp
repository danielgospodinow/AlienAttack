#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "label.hpp"

class Button
{
public:
    Button(Label* label, GameUtilities *gameUtils, std::function<void()> func);
    ~Button() {delete _label;}
    void update();
    Label* getLabel() {return _label;}

private:
    Label* _label;
    GameUtilities* _gameUtils;
    std::function<void()> _func;
};

#endif
