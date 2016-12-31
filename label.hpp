#ifndef LABEL_HPP
#define LABEL_HPP

#include "globals.hpp"
#include "game_utilities.hpp"

class Label
{
public:
    Label(const char* text, Vec2 pos, Colors color, int fontSize);
    ~Label() {SDL_DestroyTexture(_texture);}

    SDL_Texture* getTexture() {return _texture;}
    const char* getText () {return _text;}
    int getTextLenght() {return _textLenght;}
    Vec2 getPos() {return _pos;}
    Colors getColor() {return _color;}
    SDL_Rect getRect() {return _rect;}
    void setOffset(Vec2 offset) {_offset = offset;}
    Vec2 getOffset () {return _offset;}
    void changeLabelColor(Colors color);

private:
    SDL_Texture* _texture;
    const char* _text;
    int _textLenght;
    Vec2 _pos;
    Colors _color;
    SDL_Rect _rect;
    int _fontSize;
    Vec2 _offset;
};

#endif
