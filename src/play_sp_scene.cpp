#include "play_sp_scene.hpp"

PlaySPScene::PlaySPScene(): PlayScene()
{
    _ui = new UI();
}

PlaySPScene::~PlaySPScene()
{

}

void PlaySPScene::update()
{
    PlayScene::update();
}
