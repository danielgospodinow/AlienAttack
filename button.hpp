#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "label.hpp"

class Button
{
public:
    Button(Label* label, GameUtilities *gameUtils);
    ~Button() {delete _label;}
    void update();
    Label* getLabel() {return _label;}
private:
    Label* _label;
    GameUtilities* _gameUtils;
};

#endif
