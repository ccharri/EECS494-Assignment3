#include "Buzzsaw_Tower.h"

#include <stdio.h>
#include <float.h>

#include "Buzzsaw.h"
#include "Game_Level.h"
#include "Tower_Section.h"
#include "Utility.h"

using namespace std;
using namespace Zeni;

Buzzsaw_Tower::Buzzsaw_Tower(weak_ptr<Tower_Section> owner_, float cooldown_) : Tower_Weapon(owner_, cooldown_), spinning(false), timeSpinning(0), timeCooling(FLT_MAX)
{
	DAMAGE = 15;
	RANGE = 20;
  
  auto owner = owner_.lock();
  if(owner) owner->setName("Buzzsaw");
  setValue(Buzzsaw_Tower::getCost());
}

Buzzsaw_Tower::~Buzzsaw_Tower() 
{

}

bool Buzzsaw_Tower::canFire(shared_ptr<Game_Object> object)
{
	if(!Tower_Weapon::canFire(object))
		return false;

	if(spinning) 
		return false;

	if((!spinning) && (timeCooling <= (getCooldown()/2.))) 
		return false;

	if((object->getPosition() - getSection()->getPosition()).magnitude() > RANGE)
		return false;

	return true;
}

void Buzzsaw_Tower::fire()
{
	shared_ptr<Buzzsaw> saw(new Buzzsaw(shared_from_this(), getTarget(), RANGE, getCooldown()/2.));
	addProjectile(saw);
	spinning = true;

	Tower_Weapon::fire();
}

void Buzzsaw_Tower::on_logic(float time_step)
{
	//If not spinning
	if(!spinning)
	{
		//If cooldown is up
		if((timeCooling += time_step) > (getCooldown()/2.))
		{
			timeSpinning = 0;
		}
	}
	else {
		if((timeSpinning += time_step) > (getCooldown()/2.))
		{
			spinning = false;
			timeCooling = 0;
		}
		else {
			Collision::Sphere saw(getSection()->getPosition(), RANGE);
			auto collidingEnemies = findCollidingObjects(saw, Game_Level::getCurrentLevel()->getEnemies());
			for_each(collidingEnemies.begin(), collidingEnemies.end(), [&](shared_ptr<Game_Object> enemy_) 
			{
				enemy_->onDamage(DAMAGE*time_step);
			});
		}
	}

	Tower_Weapon::on_logic(time_step);
}