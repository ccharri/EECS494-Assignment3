#include "Rock_Dropper.h"

#include "Tower_Section.h"
#include "Rock.h"

Rock_Dropper::Rock_Dropper(Tower_Section* owner_, float cooldown_) : Tower_Weapon(owner_, cooldown_)
{
	DAMAGE_PER_Z_VEL = 3;
	LAUNCH_VEL = 100;
}

Rock_Dropper::~Rock_Dropper() 
{

}

bool Rock_Dropper::canFire(Game_Object* object)
{
	//TODO: Add in the parabolic checker functions.
	return Tower_Weapon::canFire(object);
}

void Rock_Dropper::fire()
{
	Zeni::Vector3f vel = Zeni::Vector3f(getTarget()->getPosition() - getSection()->getPosition()).normalized() /*get direction vector*/ * 10 /* initial force*/;
	Rock *r = new Rock(getSection()->getPosition(), vel);
	addProjectile(r);

	Tower_Weapon::fire();
}

void Rock_Dropper::on_logic(float time_step)
{
	Tower_Weapon::on_logic(time_step);
}