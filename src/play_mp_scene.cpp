#include "play_mp_scene.hpp"

PlayMPScene::PlayMPScene() : Scene()
{
    Sprite* playerSprite = new Sprite("sprites/currentSprites.png", {0, 0, globals::PLAYER_SPRITE_SIZE_X, globals::PLAYER_SPRITE_SIZE_Y}, {0,685,104,64});
    Vec2<int> playerPos = Vec2<int>(globals::GAME_WIDTH / 2 - playerSprite->getPosnsizeRect().w / 2, globals::GAME_HEIGHT - playerSprite->getPosnsizeRect().h * 1.3f);
    playerSprite->setPosition(playerPos);

    _player = new Player(playerSprite, playerPos);
    _player->setPosition(_player->getSprite()->getPosition() + Vec2<int>(-_player->getSprite()->getPosnsizeRect().w * 1.8f - 5, 0));

    _playerTwo = new Player(new Sprite("sprites/currentSprites.png", {0, 0, globals::PLAYER_SPRITE_SIZE_X, globals::PLAYER_SPRITE_SIZE_Y}, {0,685,104,64}), Vec2<int>(0, 0));
    _playerTwo->getSprite()->setAlpha(90);
    _playerTwo->setPosition(playerPos + Vec2<int>(_player->getSprite()->getPosnsizeRect().w * 1.8f, 0));
    _isPlayerTwoAI = false;
    _playerTwoAIRight= false;
    _playerTwoAITimer = 0;

    _isPlayerMovingRight = false;
    _isPlayerMovingLeft = false;
    _isPlayerShooting = false;

    _isPlayerTwoMovingRight = false;
    _isPlayerTwoMovingLeft = false;
    _isPlayerTwoShooting = false;

    _deltaTime = 0;
    _now = 0;
    _last = 0;

    _youLoseLabel = NULL;
    _youWinLabel = NULL;

    _ui = new UI(true);
    _enemyHorde = new EnemyHorde(Vec2<int>(0, 50));
    _barricades = new Barricades(_player->getPosition());
    _specialEnemy = new SpecialMonster(GameUtilities::getRandomNumber(0, 1));

    _introMusic = Mix_LoadMUS("sounds/whatIsLove.wav");
    Mix_PlayMusic(_introMusic, -1);

    _lastScore = 0;
    GameUtilities::setScore(0);
}

PlayMPScene::~PlayMPScene()
{
    clearPlayScene();
    delete _youLoseLabel;
    delete _youWinLabel;
    Mix_FreeMusic(_introMusic);
}

void PlayMPScene::clearPlayScene()
{
    erase_p(_player);
    erase_p(_playerTwo);
    erase_p(_enemyHorde);
    erase_p( _specialEnemy);
    erase_p(_barricades);
    erase_p(_ui);
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

void PlayMPScene::handleDeltaTime()
{
    _now = SDL_GetTicks();
    if(_now > _last)
    {
        _deltaTime = ((float)(_now - _last) / 1000.0f);
        _last = _now;
    }
}

bool PlayMPScene::handleDeadHorde()
{
    if(_enemyHorde->isEmpty())
    {
        erase_p( _specialEnemy);
        erase_p(_barricades);
        erase_p(_ui);

        if(!_youWinLabel)
            _youWinLabel = new Label("You win!", globals::SCREEN_CENTER, Colors::Green, 8);
        GameUtilities::renderText(_youWinLabel->getTexture(), _youWinLabel->getRect(), _youWinLabel->getOffset());

        return false;
    }

    return true;
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

void PlayMPScene::handleBarricades()
{
    _barricades->handle(_enemyHorde);
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

void PlayMPScene::handleSpecialEnemy()
{
    if(!_specialEnemy->isDead())
    {
        for(uint j=0; j<Player::getBullets().size(); j++)
        {
            Bullet* currentBullet = Player::getBullets().at(j);
            if(GameUtilities::areColliding(currentBullet->getSprite()->getPosnsizeRect(), _specialEnemy->getSize()))
            {
                GameUtilities::setScore(GameUtilities::getScore() + 100);
                currentBullet->destroy();
                _specialEnemy->kill();
            }
        }
    }

    _specialEnemy->update(_deltaTime);
}

void PlayMPScene::handlePlayer()
{
    if(!_player)
        return;

    if(_enemyHorde->isCollidingWithPlayer(_player->getPosition()) || _enemyHorde->isABulletColliding({_player->getPosition().x, _player->getPosition().y, globals::PLAYER_SPRITE_SIZE_X, globals::PLAYER_SPRITE_SIZE_Y}))
    {
        _ui->reduceHealthBarOne();
        if(_ui->getPlayerOneLives()  <= -1)
        {
            erase_p(_player);
            return;
        }
    }

    if(_isPlayerMovingLeft)
        _player->moveLeft();
    else if(_isPlayerMovingRight)
        _player->moveRight();
    if(_isPlayerShooting)
        _player->shoot();
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
