#include "play_mp_scene.hpp"

PlayMPScene::PlayMPScene() : PlayScene()
{
    _player->setPosition(_player->getSprite()->getPosition() + Vec2<int>(-_player->getSprite()->getPosnsizeRect().w * 1.8f - 5, 0));

    _playerTwo = new Player(new Sprite("sprites/currentSprites.png", {0, 0, globals::PLAYER_SPRITE_SIZE_X, globals::PLAYER_SPRITE_SIZE_Y}, {0,685,104,64}), Vec2<int>(0, 0));
    _playerTwo->getSprite()->setAlpha(90);
    _playerTwo->setPosition(_player->getSprite()->getPosition() + Vec2<int>(_player->getSprite()->getPosnsizeRect().w * 1.8f, 0));
    _isPlayerTwoAI = false;
    _playerTwoAIRight= false;
    _playerTwoAITimer = 0;

    _isPlayerTwoMovingRight = false;
    _isPlayerTwoMovingLeft = false;
    _isPlayerTwoShooting = false;

    _ui = new UI(true);
}

PlayMPScene::~PlayMPScene()
{
    clearPlayScene();
}

void PlayMPScene::clearPlayScene()
{
    erase_p(_playerTwo);
    PlayScene::clearPlayScene();
}

void PlayMPScene::update()
{
    handleDeltaTime();
    if(!handleInput()) return;
    if(!handleDeadPlayer()) return;
    if(!handleDeadHorde()) return;
    handleBarricades();
    handleSpecialEnemy();
    handlePlayer();
    handlePlayerTwo();
    handleUpdating();
}

bool PlayMPScene::handleDeadPlayer()
{
    if(!_player && !_playerTwo)
    {
        clearPlayScene();
        if(!_youLoseLabel)
            _youLoseLabel = new Label("You lose!", globals::SCREEN_CENTER, Colors::Red, 8);
        GameUtilities::renderText(_youLoseLabel->getTexture(), _youLoseLabel->getRect(), _youLoseLabel->getOffset());

        return false;
    }

    return true;
}

void PlayMPScene::handleUpdating()
{
    _ui->drawHealthBars();

    if(_player)
        _player->drawAndUpdate(_deltaTime);
    if(_playerTwo)
        _playerTwo->drawAndUpdate(_deltaTime);

    _barricades->draw();
    _enemyHorde->update(_deltaTime);

    if(_lastScore != GameUtilities::getScore())
    {
        _lastScore = GameUtilities::getScore();
        _ui->updateScoreBoard(_lastScore);
    }
    _ui->drawScoreBoard();
}

void PlayMPScene::handlePlayerTwo()
{
    if(!_playerTwo)
        return;

    if(_enemyHorde->isCollidingWithPlayer(_playerTwo->getPosition()) || _enemyHorde->isABulletColliding({_playerTwo->getPosition().x, _playerTwo->getPosition().y, globals::PLAYER_SPRITE_SIZE_X, globals::PLAYER_SPRITE_SIZE_Y}))
    {
        _ui->reduceHealthBarTwo();
        if(_ui->getPlayerTwoLives()  <= -1)
        {
            erase_p(_playerTwo);
            return;
        }
    }

    if(!_isPlayerTwoAI)
    {
        if(_isPlayerTwoMovingLeft)
            _playerTwo->moveLeft();
        else if(_isPlayerTwoMovingRight)
            _playerTwo->moveRight();
        if(_isPlayerTwoShooting)
            _playerTwo->shoot();
    }
    else
    {
        _playerTwoAITimer += 1 * _deltaTime;

        SDL_Rect playerTwoRect = _playerTwo->getSprite()->getPosnsizeRect();

        auto isUnderBarricade = [&]()
        {
            Sprite** barricads = _barricades->getBarricades();

            for(int i=0; i<globals::BARRICADES_SIZE; i++)
            {
                if(!barricads[i])
                    continue;

                if(playerTwoRect.x + playerTwoRect.w * 0.7f >= barricads[i]->getPosition().x
                        && playerTwoRect.x + playerTwoRect.w * 0.3f <= barricads[i]->getPosition().x + barricads[i]->getPosnsizeRect().w)
                    return true;
            }

            return false;
        };

        auto isUnderEnemyHorde = [&]()
        {
            if(playerTwoRect.x + playerTwoRect.w / 2 >= _enemyHorde->getHordePos().x
                    && playerTwoRect.x + playerTwoRect.w / 2 <= _enemyHorde->getHordePos().x + _enemyHorde->getHordeSize().x)
                return true;
            return false;
        };

        auto moveAIPlayer = [&]()
        {
            if(_playerTwoAITimer < 0.2f)
                return;

            if(playerTwoRect.x + playerTwoRect.w < _enemyHorde->getHordePos().x)
                _playerTwoAIRight = true;
            else if(playerTwoRect.x > _enemyHorde->getHordePos().x + _enemyHorde->getHordeSize().x)
                _playerTwoAIRight = false;
            else
                _playerTwoAIRight = GameUtilities::getRandomNumber(0, 1);

            _playerTwoAITimer = 0;
        };

        auto handleAIPlayer = [&]()
        {
            if(!isUnderBarricade() && isUnderEnemyHorde())
                _playerTwo->shoot();

            if(_playerTwoAIRight)
                _playerTwo->moveRight();
            else
                _playerTwo->moveLeft();
        };

        moveAIPlayer();
        handleAIPlayer();
    }
}

bool PlayMPScene::handleInput()
{
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
        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_LEFT)
        {
            _isPlayerTwoMovingRight = false;
            _isPlayerTwoMovingLeft = true;
        }
        else if(SDL_Components::getEvent()->key.keysym.sym == SDLK_RIGHT)
        {
            _isPlayerTwoMovingLeft = false;
            _isPlayerTwoMovingRight = true;
        }

        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_SPACE)
            _isPlayerShooting = true;

        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_KP_ENTER)
            _isPlayerTwoShooting = true;

        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_ESCAPE)
        {
            clearPlayScene();
            Game::popScene();
            return false;
        }
        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_l)
            _isPlayerTwoAI = !_isPlayerTwoAI;
    }
    else if(SDL_Components::getEvent()->type == SDL_KEYUP)
    {
        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_a)
            _isPlayerMovingLeft = false;
        else if(SDL_Components::getEvent()->key.keysym.sym == SDLK_d)
            _isPlayerMovingRight = false;

        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_SPACE)
            _isPlayerShooting = false;

        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_LEFT)
            _isPlayerTwoMovingLeft = false;
        else if(SDL_Components::getEvent()->key.keysym.sym == SDLK_RIGHT)
            _isPlayerTwoMovingRight = false;

        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_KP_ENTER)
            _isPlayerTwoShooting = false;
    }

    return true;
}
