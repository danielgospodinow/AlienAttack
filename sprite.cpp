#include "sprite.hpp"

Sprite::Sprite(const char* imageLocation, SDL_Rect sizeRect)
{
    _position = Vec2(sizeRect.x, sizeRect.y);
    _posnsizeRect = sizeRect;
    _texture = IMG_LoadTexture(SDL_Components::getRenderer(), imageLocation);
    _cropRect = {0, 0, 0, 0};

	if (_texture == NULL)
		cout << "Couldn't load image!" << endl;
}

Sprite::Sprite(const char* imageLocation, SDL_Rect sizeRect, SDL_Rect cropRect)
{
    _position = Vec2(sizeRect.x, sizeRect.y);
    _posnsizeRect = sizeRect;
    _cropRect = cropRect;
    _texture = IMG_LoadTexture(SDL_Components::getRenderer(), imageLocation);

	if (_texture == NULL)
		cout << "Couldn't load image!" << endl;
}

Sprite::Sprite(Sprite &sprite)
{
    _texture = sprite.getTexture();
    _cropRect = sprite.getCropRect();
    _posnsizeRect = sprite.getPosnsizeRect();
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(_texture);
}

void Sprite::draw()
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

void Sprite::setPosition(Vec2 position)
{
    _position = position;
	_posnsizeRect.x = position.x;
	_posnsizeRect.y = position.y;
}

Vec2 Sprite::getPosition()
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

SDL_Texture * Sprite::getTexture()
{
    return _texture;
}

SDL_Rect Sprite::getCropRect()
{
    return _cropRect;
}

SDL_Rect Sprite::getPosnsizeRect()
{
    return _posnsizeRect;
}
