#include "barricades.hpp"

Barricades::Barricades(Vec2<int> playerPos)
{
    for(int i=0; i<globals::BARRICADES_SIZE; i++)
        _barricads[i] = new Sprite("sprites/currentSprites.png", {globals::GAME_WIDTH - (i+1) * 180, playerPos.y - 90, 100, 75}, {47, 487, 176, 128});
}

Barricades::~Barricades()
{
    for(int i=0; i<globals::BARRICADES_SIZE; i++)
    {
        if(!_barricads[i])
            continue;

        delete _barricads[i];
        _barricads[i] = NULL;
    }
}

void Barricades::handle(EnemyHorde* enemyHorde)
{
    for(int i=0; i<globals::BARRICADES_SIZE; i++)
    {
        if(!enemyHorde)
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

        if(_barricads[i] && enemyHorde->isABulletColliding(_barricads[i]->getPosnsizeRect()))
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
        }
    }
}

void Barricades::draw() const
{
    for(int i=0; i<globals::BARRICADES_SIZE; i++)
        if(_barricads[i])
            _barricads[i]->draw();
}

Sprite ** const Barricades::getBarricades()
{
    return _barricads;
}
