#include "Rock_Dropper.h"

#include <stdio.h>
#include "Tower_Section.h"
#include "Rock.h"
#include "Utility.h"

using namespace std;
using namespace Zeni;

Rock_Dropper::Rock_Dropper(weak_ptr<Tower_Section> owner_, float cooldown_) : Tower_Weapon(owner_, cooldown_)
{
	DAMAGE_PER_Z_VEL = 3;
	LAUNCH_VEL = 100;
}

Rock_Dropper::~Rock_Dropper() 
{

}

bool Rock_Dropper::canFire(shared_ptr<Game_Object> object)
{
	//TODO: Add in the parabolic checker functions.
	return Tower_Weapon::canFire(object);
}

void Rock_Dropper::fire()
{
	Vector3f vel = Vector3f(getTarget()->getPosition() - getSection()->getPosition()).normalized() /*get direction vector*/ * 10. /* initial force*/;
	shared_ptr<Game_Object> r = shared_ptr<Game_Object>(new Rock(getSection()->getPosition(), vel));
	r->lookAt(getTarget()->getPosition());
	addProjectile(r);

	Tower_Weapon::fire();
}

void Rock_Dropper::on_logic(float time_step)
{
	Tower_Weapon::on_logic(time_step);
}