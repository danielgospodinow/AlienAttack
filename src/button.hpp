#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "label.hpp"

class Button
{
public:
    Button(Label* label, std::function<void()> func);
    ~Button();

    void update();

    Label* getLabel() const;

private:
    Label* _label;
    std::function<void()> _func;

    bool _clickedOnce;
};

#endif
