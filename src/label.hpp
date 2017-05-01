#ifndef LABEL_HPP
#define LABEL_HPP

#include "globals.hpp"
#include "game_utilities.hpp"

class Label
{
public:
    Label(const char* text, Vec2<int> pos, Colors color, int fontSize);
    ~Label();

    SDL_Texture* getTexture() const;
    const char* getText () const;
    int getTextLenght() const;
    Vec2<int> getPos() const;
    Colors getColor() const;
    SDL_Rect getRect() const;
    Vec2<int> getOffset () const;

    void setText(const char* text);
    void setOffset(Vec2<int> offset);
    void setLabelColor(Colors color);

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
