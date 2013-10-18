#include "Tower_Weapon.h"

#include <functional>

#include "Utility.h"
#include "Game_Level.h"
#include "Game_Object.h"
#include "Tower_Section.h"

using namespace Zeni;
using namespace std;

class FunctorHelper{
public:
	FunctorHelper(Tower_Weapon* weapon_) : weapon(weapon_) {};

	bool operator()(Game_Object* object_) {
		return weapon->canFire(object_);
	}

private:
	Tower_Weapon* weapon;
};

Tower_Weapon::Tower_Weapon(Tower_Section* owner_, float cooldown_) : owner(owner_), target(nullptr), cooldown(cooldown_), last_fired_time(0)
{

}

Tower_Weapon::~Tower_Weapon()
{
	for(Game_Object* p : projectiles)
		delete p;
}

void Tower_Weapon::removeProjectile(Game_Object* projectile_)
{
	auto it = find(projectiles.begin(), projectiles.end(), projectile_);
	if(it != projectiles.end()) projectiles.erase(it);
}

void Tower_Weapon::on_logic(float time_step)
{
	cout << "tower weapon on " << endl;
	for_each(projectiles.begin(), projectiles.end(), [&](Game_Object* object_) {
		object_->on_logic(time_step);
	});

	//If target cannot be fired upon
	if(target && !canFire(target))
	{
		//Forget target
		target = nullptr;
	}

	//If no target, find new target
	if(!target){
		FunctorHelper helper(this);
		target = closestObjectMatching(owner->getPosition(), Game_Level::getCurrentLevel()->getEnemies(), helper);
	}

	//Nothing to fire upon
	if(!target) return;

	if(fireTimer.seconds() >= (last_fired_time + cooldown))
	{
		//Fire
		fire();
	}
}

void Tower_Weapon::render()
{
	//Render self


	for_each(projectiles.begin(), projectiles.end(), [&](Game_Object* object_) {
		object_->render();
	});
}

void Tower_Weapon::fire()
{
	last_fired_time = fireTimer.seconds();
}

bool Tower_Weapon::canFire(Game_Object* object)
{
	return object->isTargetable();
}
