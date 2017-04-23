#include "game_utilities.hpp"

TTF_Font* GameUtilities::_font = NULL;
int GameUtilities::_score = 0;

void GameUtilities::init()
{
    _font = TTF_OpenFont("fonts/raidercrusader.ttf", 24);
}

void GameUtilities::close()
{
    TTF_CloseFont(_font);
}

void GameUtilities::renderText(SDL_Texture* texture, SDL_Rect rect, Vec2<int> offset)
{
    rect.x += offset.x;
    rect.y += offset.y;
    SDL_RenderCopy(SDL_Components::getRenderer(), texture, NULL, &rect);
}

int GameUtilities::getStrLen(const char *str)
{
    int lenght = 0;
    while(*str)
    {
        lenght += 1;
        str += 1;
    }
    return lenght;
}

int GameUtilities::getRandomNumber(int startRange, int endRange)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(startRange, endRange);

    return distr(eng);
}

bool GameUtilities::areColliding(SDL_Rect one, SDL_Rect two)
{
    if(!(one.x <= two.x))
    {
        SDL_Rect temp = one;
        one = two;
        two = temp;
    }

    if((one.x + one.w > two.x) && (two.y + two.h >= one.y && two.y < one.y + one.h))
        return true;
    return false;
}
