#include "Game_Level.h"

#include <algorithm>

#include "Enemy.h"
#include "Game_Object.h"
#include "Player.h"
#include "Tower_Base.h"
#include "Tower_Section.h"

using namespace Zeni;
using namespace std;

Game_Level* Game_Level::currentLevel = nullptr;

Game_Level::Game_Level()
{
	gold = 0;
}

Game_Level::~Game_Level() {
}

const std::vector<std::shared_ptr<Game_Object> > Game_Level::getEnemyObjs() const
{
    vector<shared_ptr<Game_Object> > enemyObjs;
    const vector<shared_ptr<Enemy> >& enemies = Game_Level::getCurrentLevel()->getEnemies();
    for_each(enemies.begin(), enemies.end(), [&](shared_ptr<Enemy> enemy_) {enemyObjs.push_back(std::static_pointer_cast<Game_Object>(enemy_));});
    
    return enemyObjs;
}

void Game_Level::removeEnemy(shared_ptr<Enemy> enemy){
	auto it = find(enemies.begin(), enemies.end(), enemy);
	if(it != enemies.end()) enemies.erase(it);
}


void Game_Level::render()
{
	getModel()->render();
	//player->render();
	for_each(enemies.begin(), enemies.end(), [](shared_ptr<Game_Object> object_) {if(object_) object_->render();});
	for_each(towerBases.begin(), towerBases.end(), [](shared_ptr<Tower_Base> base_) {if(base_) base_->render();});
}

void Game_Level::on_logic(float time_step)
{
	//player->on_logic(time_step);
	for_each(enemies.begin(), enemies.end(), [&](shared_ptr<Game_Object> object_) {if(object_) object_->on_logic(time_step);});
	for_each(towerBases.begin(), towerBases.end(), [&](shared_ptr<Tower_Base> base_) {if(base_) base_->on_logic(time_step);});
}

void Game_Level::enemyLeaked( std::shared_ptr<Enemy> enemy )
{
	
	if(enemy->leakAmount())
		play_sound("enemy_leaked");

	livesRemaining -= enemy->leakAmount();

	removeEnemy(enemy);
}

vector<shared_ptr<Game_Object> > Game_Level::getTowerParts() const
{
    vector<shared_ptr<Game_Object> > rVector;
    
    auto bases = getBases();
    
    for_each(bases.begin(), bases.end(), [&](shared_ptr<Tower_Base> base) {
        rVector.push_back(static_pointer_cast<Game_Object>(base));
        
        auto segments = base->getSegments();
        
        for_each(segments.begin(), segments.end(), [&](shared_ptr<Tower_Section> segment) {
            rVector.push_back(static_pointer_cast<Game_Object>(segment));
        });
    });
    
    return rVector;
}
