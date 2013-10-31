#include "Laser.h"

#include "Tower_Weapon.h"
#include "Tower_Section.h"

using namespace Zeni;
using namespace std;

Model_Wrapper Laser::model("models/laser.3ds");

Laser::Laser(std::weak_ptr<Tower_Weapon> owner_, std::weak_ptr<Game_Object> target_, float damage_, float duration_) : Game_Object(owner_.lock()->getSection()->getPosition()), timePassed(0), duration(duration_), owner(owner_), target(target_)
{
	play_sound("laser");

	auto target = target_.lock();
	if(target)
	{
		targetPos = target->getPosition();
		target->onDamage(damage_);
	}

	pointToTarget();
}

void Laser::on_logic(float time_step) 
{
	auto weapon = owner.lock();
	if(!weapon) return;

	if((timePassed += time_step) > duration)
	{
		weapon->removeProjectile(shared_from_this());
		return;
	};

	auto starget = target.lock();
	if(starget)
	{
		targetPos = starget->getPosition();
	}

	pointToTarget();
}

void Laser::pointToTarget()
{
	auto weapon = owner.lock();
	if(!weapon) return;

	float dist = Vector3f(targetPos - weapon->getSection()->getPosition()).magnitude();
	setScale(Vector3f(dist, 1., 1.));
	lookAt(targetPos);
}