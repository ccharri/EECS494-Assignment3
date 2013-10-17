#include "Game_Level.h"

#include <algorithm>

using namespace Zeni;
using namespace std;

Game_Level::~Game_Level() {
	for_each(enemies.begin(), enemies.end(), [&](Game_Object* object){
		delete object;
	});
}

Game_Object* Game_Level::getClosestEnemy(const Zeni::Point3f &loc)
{
	Game_Object* closest;
	float distance = std::numeric_limits<float>::max(); // highest possible distance
	for(Game_Object* g : enemies)
	{
		float newDistance = sqrt(pow(loc.x - g->getPosition().x, 2) + pow(loc.y - g->getPosition().y, 2) + pow(loc.z - g->getPosition().z, 2));
		if(distance > newDistance)
		{
			closest = g;
			distance = newDistance;
		}
	}
	return closest;
}

void Game_Level::removeEnemy(Game_Object* enemy){
	auto it = find(enemies.begin(), enemies.end(), enemy);
	if(it != enemies.end()) enemies.erase(it);
}