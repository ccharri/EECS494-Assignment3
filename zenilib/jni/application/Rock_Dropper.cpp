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
	LAUNCH_VEL = 25;
  
  auto owner = owner_.lock();
  if(owner) 
		owner->setName("Rock Dropper");
}

Rock_Dropper::~Rock_Dropper() 
{

}

bool Rock_Dropper::canFire(shared_ptr<Game_Object> object)
{
	if(!Tower_Weapon::canFire(object))
		return false;

	float time = getTimeIterativeParabolic(object->getPosition(), object->getVel(), getSection()->getPosition(), LAUNCH_VEL);
	if(time < 0)
		return false;

	return true;
}

void Rock_Dropper::fire()
{
	Tower_Weapon::fire();
	Point3f launchPos = getSection()->getPosition();
	Point3f targetPos = getTarget()->getPosition();
	Vector3f targetVel = getTarget()->getVel();
	float time = getTimeIterativeParabolic(targetPos, targetVel, launchPos, LAUNCH_VEL);
	targetPos = targetPos + targetVel * time;
	
	float vAngle = getAngleParabolic(targetPos, getSection()->getPosition(), LAUNCH_VEL);
	float hAngle = atan2(targetPos.y-launchPos.y, targetPos.x-launchPos.x);
	Vector3f projectileVel(cos(hAngle)*cos(vAngle) * LAUNCH_VEL, sin(hAngle)*cos(vAngle) * LAUNCH_VEL, sin(vAngle)*LAUNCH_VEL);

	shared_ptr<Game_Object> r = shared_ptr<Game_Object>(new Rock(getSection()->getPosition(), projectileVel));
	getSection()->lookAt(Point3f(targetPos.x, targetPos.y, 0));
	r->lookAt(getTarget()->getPosition());
	addProjectile(r);
	
}

void Rock_Dropper::on_logic(float time_step)
{
	Tower_Weapon::on_logic(time_step);
}