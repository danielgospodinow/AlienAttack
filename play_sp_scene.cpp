#include "play_sp_scene.hpp"

PlaySPScene::PlaySPScene(GameUtilities* gameUtils) : Scene(gameUtils)
{
    Sprite* playerSprite = new Sprite("sprites/currentSprites.png", {0, 0, globals::PLAYER_SPRITE_SIZE_X, globals::PLAYER_SPRITE_SIZE_Y}, {0,685,104,64});
    Vec2 playerPos = Vec2(globals::GAME_WIDTH / 2 - playerSprite->getPosnsizeRect().w / 2, globals::GAME_HEIGHT - playerSprite->getPosnsizeRect().h * 1.3f);
    playerSprite->setPosition(playerPos);

    _player = new Player(playerSprite, playerPos);

    _isPlayerMovingRight = false;
    _isPlayerMovingLeft = false;
    _isPlayerShooting = false;

    _deltaTime = 0;
    _now = 0;
    _last = 0;
}

PlaySPScene::~PlaySPScene()
{
    delete _player;
}

void PlaySPScene::update()
{
    _now = SDL_GetTicks();
    if(_now > _last)
    {
        _deltaTime = ((float)(_now - _last) / 1000.0f);
        _last = _now;
    }

    if(SDL_Components::getEvent()->type == SDL_KEYDOWN)
    {
        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_a)
        {
            _isPlayerMovingRight = false;
            _isPlayerMovingLeft = true;
        }
        else if(SDL_Components::getEvent()->key.keysym.sym == SDLK_d)
        {
            _isPlayerMovingLeft = false;
            _isPlayerMovingRight = true;
        }

        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_SPACE)
            _isPlayerShooting = true;

        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_ESCAPE)
        {
            Game::popScene();
        }
    }
    else if(SDL_Components::getEvent()->type == SDL_KEYUP)
    {
        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_a)
            _isPlayerMovingLeft = false;
        else if(SDL_Components::getEvent()->key.keysym.sym == SDLK_d)
            _isPlayerMovingRight = false;

        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_SPACE)
            _isPlayerShooting = false;
    }

    if(_isPlayerMovingLeft)
        _player->moveLeft(_deltaTime);
    else if(_isPlayerMovingRight)
        _player->moveRight(_deltaTime);

    if(_isPlayerShooting)
        _player->shoot();

    _player->drawAndUpdate(_deltaTime);
}
