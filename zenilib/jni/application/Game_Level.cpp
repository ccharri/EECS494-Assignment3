#include "Game_Level.h"

#include <algorithm>

using namespace Zeni;
using namespace std;

Game_Level::~Game_Level() {
	for_each(enemies.begin(), enemies.end(), [&](Game_Object* object){
		delete object;
	});
}

void Game_Level::removeEnemy(Game_Object* enemy){
	auto it = find(enemies.begin(), enemies.end(), enemy);
	if(it != enemies.end()) enemies.erase(it);
}