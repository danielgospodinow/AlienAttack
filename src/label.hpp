#ifndef LABEL_HPP
#define LABEL_HPP

#include "globals.hpp"
#include "game_utilities.hpp"

class Label
{
public:
    Label(const char* text, Vec2<int> pos, Colors color, int fontSize);
    ~Label() {SDL_DestroyTexture(_texture);}

    SDL_Texture* getTexture() {return _texture;}
    const char* getText () {return _text;}
    void setText(const char* text);
    int getTextLenght() {return _textLenght;}
    Vec2<int> getPos() {return _pos;}
    Colors getColor() {return _color;}
    SDL_Rect getRect() {return _rect;}
    void setOffset(Vec2<int> offset) {_offset = offset;}
    Vec2<int> getOffset () {return _offset;}
    void changeLabelColor(Colors color);

private:
    SDL_Texture* _texture;
    const char* _text;
    int _textLenght;
    Vec2<int> _pos;
    Colors _color;
    SDL_Rect _rect;
    int _fontSize;
    Vec2<int> _offset;
};

#endif
