#include "Game_Level.h"

#include <algorithm>

#include "Game_Object.h"
#include "Player.h"
#include "Tower_Base.h"

using namespace Zeni;
using namespace std;

Game_Level* Game_Level::currentLevel = nullptr;

Game_Level::Game_Level()
{

}

Game_Level::~Game_Level() {
}

void Game_Level::removeEnemy(shared_ptr<Game_Object> enemy){
	auto it = find(enemies.begin(), enemies.end(), enemy);
	if(it != enemies.end()) enemies.erase(it);
}


void Game_Level::render()
{
	getModel()->render();
	//player->render();
	for_each(enemies.begin(), enemies.end(), [](shared_ptr<Game_Object> object_) {object_->render();});
	for_each(towerBases.begin(), towerBases.end(), [](shared_ptr<Tower_Base> base_) {base_->render();});
}

void Game_Level::on_logic(float time_step)
{
	//player->on_logic(time_step);
	for_each(enemies.begin(), enemies.end(), [&](shared_ptr<Game_Object> object_) {object_->on_logic(time_step);});
	for_each(towerBases.begin(), towerBases.end(), [&](shared_ptr<Tower_Base> base_) {base_->on_logic(time_step);});
}