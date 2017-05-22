#include "highscores_scene.hpp"

HighscoreScene::HighscoreScene() :
    _labels()
{
    //for(int i=0; i<globals::MAX_HIGHSCORES; i++) Line 4 replaces this
    //    _labels[i] = NULL;

    if(GameUtilities::getHighscores()[0] == 0)
    {
        _labels[0] = new Label("No Highscores!", globals::SCREEN_CENTER, Colors::Yellow, 7);
        return;
    }

    for(int i=0; i<globals::MAX_HIGHSCORES; i++)
    {
        if(GameUtilities::getHighscores()[i] == 0)
            break;

        _labels[i] = new Label((std::to_string(i + 1) + ". " + std::to_string(GameUtilities::getHighscores()[i])).c_str(), Vec2<int>(globals::SCREEN_CENTER.x, globals::GAME_HEIGHT / 6 + i*42), Colors::Green, 5); //make this scalable, not hardcoded
    }
}

HighscoreScene::~HighscoreScene()
{
    clearScene();
}

void HighscoreScene::update()
{
    for(int i=0; i<globals::MAX_HIGHSCORES; i++)
    {
        if(!_labels[i])
            break;

        GameUtilities::renderText(_labels[i]->getTexture(), _labels[i]->getRect(), _labels[i]->getOffset());
    }

    handleInput();
}

void HighscoreScene::handleInput()
{
    if(SDL_Components::getEvent()->type == SDL_KEYDOWN && SDL_Components::getEvent()->key.keysym.sym == SDLK_ESCAPE)
    {
        clearScene();
        Game::popScene();
    }
}

void HighscoreScene::clearScene()
{
    for(int i=0; i<globals::MAX_HIGHSCORES; i++)
        erase_p(_labels[i]);
}
