#include "label.hpp"

Label::Label(const char* text, Vec2<int> pos, Colors color, int fontSize) :
    _text(NULL), _textLenght(GameUtilities::getStrLen(text)), _pos(pos), _color(color), _fontSize(fontSize)
  //!!! greshno li e _text(text)?
{
    setTextInternal(text);

    (_fontSize>8)?_fontSize=8:_fontSize = _fontSize;

    SDL_Surface* surface = NULL;
    SDL_Color fontColor  = getColorInternal(color);

    surface = TTF_RenderText_Solid(GameUtilities::getFont(), _text, fontColor);
    _texture = SDL_CreateTextureFromSurface(SDL_Components::getRenderer(), surface);

    SDL_FreeSurface(surface);

    _rect.w = _textLenght * (globals::LABEL_WIDTH_SCALER * fontSize);
    _rect.h = globals::LABEL_HEIGHT_SCALER * fontSize;
    _rect.x = _pos.x - _rect.w / 2;
    _rect.y = _pos.y - _rect.h / 2;
}

void Label::setTextInternal(const char *newText)
{
    delete[] _text;

    _text = new char[GameUtilities::getStrLen(newText) + 1];
    strcpy(_text, newText);
}

//Label::Label(const Label &other)
//{
//    //this = other;
//}

//Label& Label::operator =(const Label& other)
//{

//}

Label::~Label()
{
    SDL_DestroyTexture(_texture);
    delete [] _text;
}

void Label::setText(const char *text)
{
    setTextInternal(text);
    _textLenght = GameUtilities::getStrLen(text);
    SDL_Surface* surface = NULL;
    SDL_Color fontColor = getColorInternal(_color);

    surface = TTF_RenderText_Solid(GameUtilities::getFont(), text, fontColor);
    _texture = SDL_CreateTextureFromSurface(SDL_Components::getRenderer(), surface);
    SDL_FreeSurface(surface);
    _rect.w = _textLenght * (globals::LABEL_WIDTH_SCALER * _fontSize);
    _rect.h = globals::LABEL_HEIGHT_SCALER * _fontSize;
    _rect.x = _pos.x - _rect.w / 2;
    _rect.y = _pos.y - _rect.h / 2;
}

void Label::setLabelColor(Colors color)
{
    if(_color == color)
        return;

    SDL_Color fontColor = getColorInternal(color);
    SDL_SetTextureColorMod(_texture, fontColor.r, fontColor.g, fontColor.b);
    _color = color;
}

SDL_Color Label::getColorInternal(Colors color) const
{
    SDL_Color newColor;

    switch(color)
    {
    case White: newColor = {255, 255, 255}; break;
    case Black: newColor = {0, 0, 0}; break;
    case Blue: newColor = {0, 0, 255}; break;
    case Red: newColor = {255, 0, 0}; break;
    case Green: newColor = {0, 255, 0}; break;
    case Yellow: newColor = {255, 255, 0}; break;
    }

    return newColor;
}

SDL_Texture* Label::getTexture() const {return _texture;}
const char* Label::getText () const {return _text;}
int Label::getTextLenght() const {return _textLenght;}
Vec2<int> Label::getPos() const {return _pos;}
Colors Label::getColor() const {return _color;}
SDL_Rect Label::getRect() const {return _rect;}
Vec2<int> Label::getOffset () const {return _offset;}

void Label::setOffset(Vec2<int> offset) {_offset = offset;}
