#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "globals.hpp"
#include "sdl_components.hpp"

class Sprite
{
public:
	Sprite(const char* imageLocation, SDL_Rect sizeRect);
	Sprite(const char* imageLocation, SDL_Rect sizeRect, SDL_Rect cropRect);
	Sprite(Sprite& sprite);
	~Sprite();

	Sprite& operator=(Sprite& sprite)
	{
        _texture = sprite.getTexture();
        _cropRect = sprite.getCropRect();
        _posnsizeRect = sprite.getPosnsizeRect();

		return *this;
	}

	void draw();

	void setupSprite(SDL_Texture* texture, SDL_Rect cropRect, SDL_Rect posnsizeRect);

    void setPosition(Vec2<int> position);
	void setTexture(SDL_Texture* texture);
	void setCropRect(SDL_Rect cropRect);
	void setPosnsizeRect(SDL_Rect posnsizeRect);
    void setAlpha(int alpha);

	SDL_Texture* getTexture();
	SDL_Rect getCropRect();
	SDL_Rect getPosnsizeRect();
    Vec2<int> getPosition();
    int getAlpha() {return _alpha;}

private:
	SDL_Texture* _texture;
	SDL_Rect _cropRect;
	SDL_Rect _posnsizeRect;
    Vec2<int> _position;
    int _alpha;
};

#endif
