#include "sprite.hpp"

Sprite::Sprite(const char* imageLocation, SDL_Rect sizeRect)
{
    _position = Vec2<int>(sizeRect.x, sizeRect.y);
    _posnsizeRect = sizeRect;
    _texture = IMG_LoadTexture(SDL_Components::getRenderer(), imageLocation);
    _cropRect = {0, 0, 0, 0};
    _alpha = 100;

	if (_texture == NULL)
		cout << "Couldn't load image!" << endl;
}

Sprite::Sprite(const char* imageLocation, SDL_Rect sizeRect, SDL_Rect cropRect)
{
    _position = Vec2<int>(sizeRect.x, sizeRect.y);
    _posnsizeRect = sizeRect;
    _cropRect = cropRect;
    _texture = IMG_LoadTexture(SDL_Components::getRenderer(), imageLocation);
    _alpha = 100;

	if (_texture == NULL)
		cout << "Couldn't load image!" << endl;
}

Sprite::Sprite(const Sprite& sprite)
{
    *this = sprite;
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(_texture);
}

Sprite& Sprite::operator=(const Sprite& sprite)
{
    _texture = sprite.getTexture();
    _cropRect = sprite.getCropRect();
    _posnsizeRect = sprite.getPosnsizeRect();

    return *this;
}

void Sprite::draw() const
{
    if(_cropRect.w == 0)
        SDL_RenderCopy(SDL_Components::getRenderer(), _texture, NULL, &_posnsizeRect);
	else
        SDL_RenderCopy(SDL_Components::getRenderer(), _texture, &_cropRect, &_posnsizeRect);
}

void Sprite::setupSprite(SDL_Texture * texture, SDL_Rect cropRect, SDL_Rect posnsizeRect)
{
    setTexture(texture);
    setCropRect(cropRect);
    setPosnsizeRect(posnsizeRect);
}

void Sprite::setPosition(Vec2<int> position)
{
    _position = position;
	_posnsizeRect.x = position.x;
	_posnsizeRect.y = position.y;
}

void Sprite::setAlpha(int alpha)
{
    _alpha = alpha;

    SDL_SetTextureAlphaMod(_texture, alpha);
}

Vec2<int> Sprite::getPosition() const
{
    return _position;
}

void Sprite::setTexture(SDL_Texture * texture)
{
    _texture = texture;
}

void Sprite::setCropRect(SDL_Rect cropRect)
{
    _cropRect = cropRect;
}

void Sprite::setPosnsizeRect(SDL_Rect posnsizeRect)
{
    _posnsizeRect = posnsizeRect;
}

SDL_Texture * Sprite::getTexture() const
{
    return _texture;
}

SDL_Rect Sprite::getCropRect() const
{
    return _cropRect;
}

SDL_Rect Sprite::getPosnsizeRect() const
{
    return _posnsizeRect;
}

int Sprite::getAlpha() const
{
     return _alpha;
}
