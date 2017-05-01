#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "globals.hpp"
#include "sdl_components.hpp"

class Sprite
{
public:
	Sprite(const char* imageLocation, SDL_Rect sizeRect);
	Sprite(const char* imageLocation, SDL_Rect sizeRect, SDL_Rect cropRect);
    Sprite(const Sprite &sprite);
	~Sprite();

    Sprite& operator=(const Sprite& sprite);

    void draw() const;

	void setupSprite(SDL_Texture* texture, SDL_Rect cropRect, SDL_Rect posnsizeRect);

    void setPosition(Vec2<int> position);
	void setTexture(SDL_Texture* texture);
	void setCropRect(SDL_Rect cropRect);
	void setPosnsizeRect(SDL_Rect posnsizeRect);
    void setAlpha(int alpha);

    SDL_Texture* getTexture() const;
    SDL_Rect getCropRect() const;
    SDL_Rect getPosnsizeRect() const;
    Vec2<int> getPosition() const;
    int getAlpha() const;

private:
	SDL_Texture* _texture;
	SDL_Rect _cropRect;
	SDL_Rect _posnsizeRect;
    Vec2<int> _position;
    int _alpha;
};

#endif
