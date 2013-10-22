#include "Tower_Weapon.h"

#include <functional>
#include <algorithm>

#include "Utility.h"
#include "Game_Level.h"
#include "Game_Object.h"
#include "Tower_Section.h"

using namespace Zeni;
using namespace std;

class FunctorHelper{
public:
	FunctorHelper(shared_ptr<Tower_Weapon> weapon_) : weapon(weapon_) {};

	bool operator()(shared_ptr<Game_Object> object_) {
		if(object_)
			return weapon->canFire(object_);
		else {
			return false;
		}
	}

private:
	shared_ptr<Tower_Weapon> weapon;
};

Tower_Weapon::Tower_Weapon(weak_ptr<Tower_Section> owner_, float cooldown_) : /*Game_Object(),*/ owner(owner_), target(), cooldown(cooldown_), last_fired_time(-cooldown_)
{
	fireTimer.start();
}

Tower_Weapon::~Tower_Weapon()
{
}

void Tower_Weapon::removeProjectile(shared_ptr<Game_Object> projectile_)
{
	auto it = find(projectiles.begin(), projectiles.end(), projectile_);
	if(it != projectiles.end()) projectiles.erase(it);
}

void Tower_Weapon::on_logic(float time_step)
{
	for_each(projectiles.begin(), projectiles.end(), [&](shared_ptr<Game_Object> object_) {
		if(object_)
		{
			object_->on_logic(time_step);

			if(Vector3f(object_->getPosition()).magnitude() > Game_Level::getCurrentLevel()->getMaxDistance())
			{
				removeProjectile(object_);
			}
		}
	});

	shared_ptr<Game_Object> tar = target.lock();

	//If target cannot be fired upon
	if(tar && !canFire(tar))
	{
		//Forget target
		tar = nullptr;
	}

	//If no target, find new target
	if(!tar){
		FunctorHelper helper(shared_from_this());
		target = closestObjectMatching(owner.lock()->getPosition(), Game_Level::getCurrentLevel()->getEnemies(), helper);
	}

	tar = target.lock();

	//Nothing to fire upon
	if(!tar) return;

	if(fireTimer.seconds() >= (last_fired_time + cooldown))
	{
		//Fire
		fire();
	}
}

void Tower_Weapon::render()
{
	//Render self
	//Game_Object::render();

	for_each(projectiles.begin(), projectiles.end(), [&](shared_ptr<Game_Object> object_) {
		if(object_)
			object_->render();
	});
}

void Tower_Weapon::fire()
{
	last_fired_time = fireTimer.seconds();
}

bool Tower_Weapon::canFire(shared_ptr<Game_Object> object)
{
	return object->isTargetable();
}
