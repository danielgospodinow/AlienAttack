#include "play_scene.hpp"

PlayScene::PlayScene(): Scene()
{
    Sprite* playerSprite = new Sprite("sprites/currentSprites.png", {0, 0, globals::PLAYER_SPRITE_SIZE_X, globals::PLAYER_SPRITE_SIZE_Y}, {0,685,104,64});
    Vec2<int> playerPos = Vec2<int>(globals::GAME_WIDTH / 2 - playerSprite->getPosnsizeRect().w / 2, globals::GAME_HEIGHT - playerSprite->getPosnsizeRect().h * 1.3f);
    playerSprite->setPosition(playerPos);

    _player = new Player(playerSprite, playerPos);

    _isPlayerMovingRight = false;
    _isPlayerMovingLeft = false;
    _isPlayerShooting = false;

    _deltaTime = 0;
    _now = 0;
    _last = 0;

    _lastScore = 0;
    GameUtilities::setScore(0);

    _youLoseLabel = NULL;
    _youWinLabel = NULL;

    //_ui = new UI();
    _enemyHorde = new EnemyHorde(Vec2<int>(0, 50));
    _barricades = new Barricades(_player->getPosition());
    _specialEnemy = new SpecialMonster(GameUtilities::getRandomNumber(0, 1));

    _introMusic = Mix_LoadMUS("sounds/whatIsLove.wav");
    Mix_PlayMusic(_introMusic, -1);
}

PlayScene::~PlayScene()
{
    clearPlayScene();
    delete _youLoseLabel;
    delete _youWinLabel;
    Mix_FreeMusic(_introMusic);
}

void PlayScene::clearPlayScene()
{
    erase_p(_player);
    erase_p(_enemyHorde);
    erase_p(_specialEnemy)
    erase_p(_barricades);
    erase_p(_ui);
}

void PlayScene::update()
{
    handleDeltaTime();
    if(!handleInput()) return;
    if(!handleDeadPlayer()) return;
    if(!handleDeadHorde()) return;
    handleBarricades();
    handleSpecialEnemy();
    handlePlayer();
    handleUpdating();
}

void PlayScene::handleDeltaTime()
{
    _now = SDL_GetTicks();
    if(_now > _last)
    {
        _deltaTime = ((float)(_now - _last) / 1000.0f);
        _last = _now;
    }
}

void PlayScene::handleBarricades()
{
    _barricades->handle(_enemyHorde);
}

bool PlayScene::handleDeadHorde()
{
    if(_enemyHorde->isEmpty())
    {
        erase_p( _specialEnemy);
        erase_p(_barricades);
        erase_p(_ui);

        if(!_youWinLabel)
        {
            _youWinLabel = new Label("You win!", globals::SCREEN_CENTER, Colors::Green, 8);
            GameUtilities::updateHighScores();
        }
        GameUtilities::renderText(_youWinLabel->getTexture(), _youWinLabel->getRect(), _youWinLabel->getOffset());

        return false;
    }

    return true;
}

bool PlayScene::handleDeadPlayer()
{
    if(!_player)
    {
        clearPlayScene();
        if(!_youLoseLabel)
        {
            _youLoseLabel = new Label("You lose!", globals::SCREEN_CENTER, Colors::Red, 8);
            GameUtilities::updateHighScores();
        }
        GameUtilities::renderText(_youLoseLabel->getTexture(), _youLoseLabel->getRect(), _youLoseLabel->getOffset());

        return false;
    }

    return true;
}

void PlayScene::handleUpdating()
{
    _ui->drawHealthBars();

    if(_player)
        _player->drawAndUpdate(_deltaTime);

    _barricades->draw();
    _enemyHorde->update(_deltaTime);

    if(_lastScore != GameUtilities::getScore())
    {
        _lastScore = GameUtilities::getScore();
        _ui->updateScoreBoard(_lastScore);
    }
    _ui->drawScoreBoard();
}

void PlayScene::handleSpecialEnemy()
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

void PlayScene::handlePlayer()
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

bool PlayScene::handleInput()
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

        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_SPACE)
            _isPlayerShooting = true;

        if(SDL_Components::getEvent()->key.keysym.sym == SDLK_ESCAPE)
        {
            clearPlayScene();
            Game::popScene();
            return false;
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

    return true;
}
