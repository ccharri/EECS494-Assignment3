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
	for_each(enemies.begin(), enemies.end(), [&](Game_Object* object){
		delete object;
	});
}

void Game_Level::removeEnemy(Game_Object* enemy){
	auto it = find(enemies.begin(), enemies.end(), enemy);
	if(it != enemies.end()) enemies.erase(it);
}


void Game_Level::render()
{
	getModel()->render();
	//player->render();
	for_each(enemies.begin(), enemies.end(), [](Game_Object* object_) {object_->render();});
	for_each(towerBases.begin(), towerBases.end(), [](Tower_Base* base_) {base_->render();});
}

void Game_Level::on_logic(float time_step)
{
	//player->on_logic(time_step);
	for_each(enemies.begin(), enemies.end(), [&](Game_Object* object_) {object_->on_logic(time_step);});
	for_each(towerBases.begin(), towerBases.end(), [&](Tower_Base* base_) {base_->on_logic(time_step);});
}