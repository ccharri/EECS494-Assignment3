#include "Rock_Dropper.h"
#include "Utility.h"
#include "Game_Level.h"
#include "Tower_Section.h"

Rock_Dropper::Rock_Dropper(Tower_Section* owner_, float cooldown_) : Tower_Weapon(owner_, cooldown_)
{
	DAMAGE_PER_Z_VEL = 3;
	LAUNCH_VEL = 100;

}

bool Rock_Dropper::canFire(Game_Object* object)
{
	//TODO: Add in the parabolic checker functions.
	return true;
}

void Rock_Dropper::fire()
{
	Zeni::Vector3f vel = Zeni::Vector3f(getTarget()->getPosition() - getSection()->getPosition()) * 0.05;
	Rock *r = new Rock(getSection()->getPosition(), vel);
	addProjectile(r);
}