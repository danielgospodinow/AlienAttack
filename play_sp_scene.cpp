#include "play_sp_scene.hpp"

int PlaySPScene::_score = 0;
bool PlaySPScene::_labelUpToDate = true;

PlaySPScene::PlaySPScene() : Scene()
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

    _youLoseLabel = new Label("You lose!", globals::SCREEN_CENTER, Colors::Red, 8);

    for(int i=0; i<globals::BARRICADES_SIZE; i++)
        _barricads[i] = new Sprite("sprites/currentSprites.png", {globals::GAME_WIDTH - (i+1) * 180, _player->getPosition().y - 90, 100, 75}, {47, 487, 176, 128});

    _specialEnemy = new SpecialMonster(GameUtilities::getRandomNumber(0, 1));

    _scoreTextLabel = new Label("Score: ", Vec2(0, 0), Colors::White, 3);
    _scoreTextLabel->setOffset(Vec2(_scoreTextLabel->getRect().w / 1.9f, _scoreTextLabel->getRect().h * 0.8f));
    _scoreNumLabel = new Label("0", Vec2(_scoreTextLabel->getPos().x + _scoreTextLabel->getRect().w * 1.5f, _scoreTextLabel->getOffset().y), Colors::Green, 3);

    _introMusic = Mix_LoadMUS("sounds/whatIsLove.mp3");
    Mix_PlayMusic(_introMusic, -1);

    _healthBar = new HealthBar(3);

    _score = 0;
}

PlaySPScene::~PlaySPScene()
{
    if(_enemyHorde)
        delete _enemyHorde;
    if(_player)
        delete _player;
    if(_specialEnemy)
        delete _specialEnemy;
    delete _youLoseLabel;
    delete _scoreTextLabel;
    delete _scoreNumLabel;

    for(int i=0; i<globals::BARRICADES_SIZE; i++)
    {
        if(!_barricads[i])
            continue;

        delete _barricads[i];
    }

    Mix_FreeMusic(_introMusic);
    delete _healthBar;
}

void PlaySPScene::update()
{
    handleDeltaTime();
    if(!handleInput()) return;
    if(!handleDeadPlayer()) return;
    handleBarricades();
    handleSpecialEnemy();
    handlePlayer();
    handleUpdating();
}

void PlaySPScene::handleDeltaTime()
{
    _now = SDL_GetTicks();
    if(_now > _last)
    {
        _deltaTime = ((float)(_now - _last) / 1000.0f);
        _last = _now;
    }
}

bool PlaySPScene::handleInput()
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

bool PlaySPScene::handleDeadPlayer()
{
    if(!_player)
    {
        GameUtilities::renderText(_youLoseLabel->getTexture(), _youLoseLabel->getRect(), _youLoseLabel->getOffset());
        return false;
    }
    else if(!_player->isAlive())
    {
        clearPlayScene();
        return false;
    }

    return true;
}

void PlaySPScene::clearPlayScene()
{
    delete _player;
    _player = NULL;
    delete _enemyHorde;
    _enemyHorde = NULL;
    delete _specialEnemy;
    _specialEnemy = NULL;

    for(int i=0; i<4; i++)
    {
        if(!_barricads[i])
            continue;

        delete _barricads[i];
        _barricads[i] = NULL;
    }
}

void PlaySPScene::handleBarricades()
{
    for(int i=0; i<globals::BARRICADES_SIZE; i++)
    {
        if(!_enemyHorde)
            return;
        if(!_barricads[i])
            continue;

        auto damageBarricade = [&]()
        {
            if(_barricads[i]->getAlpha() <= 40)
            {
                delete _barricads[i];
                _barricads[i] = NULL;
                return;
            }

            _barricads[i]->setAlpha(_barricads[i]->getAlpha() - 10);
        };

        if(_barricads[i] && _enemyHorde->isABulletColliding(_barricads[i]->getPosnsizeRect()))
            damageBarricade();

        for(Uint32 j=0; j<Player::getBullets().size(); j++)
        {
            if(!_barricads[i])
                break;

            Bullet* currentBullet = Player::getBullets().at(j);
            if(GameUtilities::areColliding(currentBullet->getSprite()->getPosnsizeRect(), _barricads[i]->getPosnsizeRect()))
            {
                currentBullet->destroy();
                damageBarricade();
            }
            else if(GameUtilities::areColliding(currentBullet->getSprite()->getPosnsizeRect(), _specialEnemy->getSize()))
            {
                setScore(getScore() + 50);
                currentBullet->destroy();
                _specialEnemy->kill();
            }
        }
    }
}

void PlaySPScene::handleUpdating()
{
    _healthBar->update();
    _player->drawAndUpdate(_deltaTime);

    for(int i=0; i<globals::BARRICADES_SIZE; i++)
        if(_barricads[i])
            _barricads[i]->draw();

    _enemyHorde->update(_deltaTime);

    if(!_labelUpToDate)
    {
        _labelUpToDate = true;
        _scoreNumLabel->setText(to_string(_score).c_str());
    }

    GameUtilities::renderText(_scoreTextLabel->getTexture(), _scoreTextLabel->getRect(), _scoreTextLabel->getOffset());
    GameUtilities::renderText(_scoreNumLabel->getTexture(), _scoreNumLabel->getRect(), _scoreNumLabel->getOffset());
}

void PlaySPScene::handleSpecialEnemy()
{
    for(Uint32 j=0; j<Player::getBullets().size(); j++)
    {
        Bullet* currentBullet = Player::getBullets().at(j);
        if(GameUtilities::areColliding(currentBullet->getSprite()->getPosnsizeRect(), _specialEnemy->getSize()))
        {
            setScore(getScore() + 50);
            currentBullet->destroy();
            _specialEnemy->kill();
        }
    }

    _specialEnemy->update(_deltaTime);
}

void PlaySPScene::handlePlayer()
{
    if(_enemyHorde->isCollidingWithPlayer(_player->getPosition()) || _enemyHorde->isABulletColliding({_player->getPosition().x, _player->getPosition().y, globals::PLAYER_SPRITE_SIZE_X, globals::PLAYER_SPRITE_SIZE_Y}))
    {
        _healthBar->reduce();
        if(_healthBar->getLives() <= -1)
        {
            _player->kill();
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
