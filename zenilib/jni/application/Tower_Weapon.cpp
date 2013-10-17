#include "Tower_Weapon.h"

#include "Utility.h"
#include "Game_Level.h"
#include "Tower_Section.h"

using namespace Zeni;
using namespace std;

void Tower_Weapon::on_logic(float time_step)
{
	//If target cannot be fired upon
	if(target && !canFire(target))
	{
		//Forget target
		target = nullptr;
	}

	//If no target, find new target
	if(!target){
		//Find closest target that this can fire upon
		target = closestObjectMatching(owner->getPosition(), Game_Level::getCurrentLevel()->getEnemies(), &this->canFire);
	}

	//Nothing to fire upon
	if(!target) return;

	//Fire
	fire();
}