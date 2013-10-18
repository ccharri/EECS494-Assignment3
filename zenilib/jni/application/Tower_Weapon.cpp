#include "Tower_Weapon.h"

#include "Utility.h"
#include "Game_Level.h"
#include "Game_Object.h"
#include "Tower_Section.h"

using namespace Zeni;
using namespace std;

Tower_Weapon::Tower_Weapon(Tower_Section* owner_, float cooldown_) : owner(owner_), target(nullptr), cooldown(cooldown_), last_fired_time(0)
{

}

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

	if(fireTimer.seconds() >= (last_fired_time + cooldown))
	{
		//Fire
		fire();
		last_fired_time = fireTimer.seconds();
	}
}

bool Tower_Weapon::canFire(Game_Object* object) const
{
	return object->isTargetable();
}