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

    _enemyHorde = new EnemyHorde(Vec2(0, 50));

    _youLoseLabel = new Label("You lose!", globals::SCREEN_CENTER, Colors::Red, 6);

    for(int i=0; i<globals::BARRICADES_SIZE; i++)
        _barricads[i] = new Sprite("sprites/currentSprites.png", {globals::GAME_WIDTH - (i+1) * 180, _player->getPosition().y - 90, 100, 75}, {47, 487, 176, 128});
}

PlaySPScene::~PlaySPScene()
{
    delete _enemyHorde;
    delete _player;
    delete _youLoseLabel;

    for(int i=0; i<globals::BARRICADES_SIZE; i++)
    {
        if(!_barricads[i])
            continue;

        delete _barricads[i];
    }
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
            return;
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

    if(!_player)
    {
        GameUtilities::renderText(_youLoseLabel->getTexture(), _youLoseLabel->getRect(), _youLoseLabel->getOffset());
        return;
    }
    else if(!_player->isAlive())
    {
        delete _player;
        _player = NULL;
        delete _enemyHorde;
        _enemyHorde = NULL;
        for(int i=0; i<4; i++)
        {
            if(!_barricads[i])
                continue;

            delete _barricads[i];
            _barricads[i] = NULL;
        }
        return;
    }

    for(int i=0; i<globals::BARRICADES_SIZE; i++)
    {
        if(!_barricads[i])
            continue;

        auto damageBarricade = [&]()
        {
            if(_barricads[i]->getAlpha() <= 0)
            {
                delete _barricads[i];
                _barricads[i] = NULL;
            }

            if(_barricads[i])
                _barricads[i]->setAlpha(_barricads[i]->getAlpha() - 10);
        };

        if(_enemyHorde->isABulletColliding(_barricads[i]->getPosnsizeRect()))
            damageBarricade();

        for(Uint32 j=0; j<Player::getBullets().size(); j++)
        {
            Bullet* currentBullet = Player::getBullets().at(j);
            if(GameUtilities::areColliding(currentBullet->getSprite()->getPosnsizeRect(), _barricads[i]->getPosnsizeRect()))
            {
                currentBullet->destroy();
                damageBarricade();
            }
        }
    }

    if(_enemyHorde->isCollidingWithPlayer(_player->getPosition()) || _enemyHorde->isABulletColliding({_player->getPosition().x, _player->getPosition().y, globals::PLAYER_SPRITE_SIZE_X, globals::PLAYER_SPRITE_SIZE_Y}))
        _player->kill();

    if(_isPlayerMovingLeft)
        _player->moveLeft(_deltaTime);
    else if(_isPlayerMovingRight)
        _player->moveRight(_deltaTime);

    if(_isPlayerShooting)
        _player->shoot();

    _player->drawAndUpdate(_deltaTime);

    _enemyHorde->update(_deltaTime);

    for(int i=0; i<globals::BARRICADES_SIZE; i++)
        if(_barricads[i])
            _barricads[i]->draw();
}
